// All rights complied to VRMonkey

#include "OculusIAP.h"
#include "CallbackMessagePoller.h"
#include "OculusIAPCallbackProxy.h"


UOculusIAPCallbackProxy::UOculusIAPCallbackProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetFlags(RF_StrongRefOnFrame);
	
	//Delegates binding
	UserIAPCheckCompleteDelegate.BindUObject(this, &UOculusIAPCallbackProxy::OnUserIAPCheckCompleteDelegate);
}


/*
Checks wether the user is entitled to the input item sku
@return bIsViewerEntitled
*/
void UOculusIAPCallbackProxy::VerifyIAPEntitlement(const char* sku) {

	ovrMessageType MessageType = ovrMessage_IAP_GetViewerPurchases;

	this->Targetsku = ANSI_TO_TCHAR(sku);

	if (ovr_IsPlatformInitialized() == true)
	{
		auto requestId = ovr_IAP_GetViewerPurchases(); // Perform the request

		UE_LOG(LogTemp, Warning, TEXT("OCULUS REQUEST SENT. Id: %d"), (int)requestId);
		if (requestId == invalidRequestID)
		{
			OnFailure.Broadcast();
		}
		else // Start polling messages
		{
			FAutoDeleteAsyncTask<FCallbackMessagePoller>* MessagePollTask = new FAutoDeleteAsyncTask<FCallbackMessagePoller>(MessageType, &UserIAPCheckCompleteDelegate);
			MessagePollTask->StartBackgroundTask();
		}
	}
	else
	{
		log("OCULUS PLATFORM UNINITIALIZED");
		OnFailure.Broadcast();
	}
}

/*
Fetches the server for the present game's full price
@return price in dollars
*/
void UOculusIAPCallbackProxy::FetchIAPPrice(const char** sku) {

	ovrMessageType MessageType = ovrMessage_IAP_GetProductsBySKU;

	if (ovr_IsPlatformInitialized() == true)
	{
		auto requestId = ovr_IAP_GetProductsBySKU(sku, 1); // Perform the request

		UE_LOG(LogTemp, Warning, TEXT("OCULUS REQUEST SENT. Id: %d"), (int)requestId);
		if (requestId == invalidRequestID)
		{
			OnFailure.Broadcast();
		}
		else // Start polling messages
		{
			FAutoDeleteAsyncTask<FCallbackMessagePoller>* MessagePollTask = new FAutoDeleteAsyncTask<FCallbackMessagePoller>(MessageType, &UserIAPCheckCompleteDelegate);
			MessagePollTask->StartBackgroundTask();
		}
	}
	else
	{
		log("OCULUS PLATFORM UNINITIALIZED");
		OnFailure.Broadcast();
	}
	//ovr_Product_GetFormattedPrice();
}


void UOculusIAPCallbackProxy::LaunchStoreCheckout(const char* sku) {

	ovrMessageType MessageType = ovrMessage_IAP_LaunchCheckoutFlow;

	if (ovr_IsPlatformInitialized() == true)
	{
		auto requestId = ovr_IAP_LaunchCheckoutFlow(sku);
		UE_LOG(LogTemp, Warning, TEXT("OCULUS REQUEST SENT. Id: %d"), (int)requestId);
		if (requestId == invalidRequestID)
			OnFailure.Broadcast();
	}
	else
	{
		log("OCULUS PLATFORM UNINITIALIZED");
		OnFailure.Broadcast();
	}

	if (ovr_IsPlatformInitialized() == true)
	{
		auto requestId = ovr_IAP_LaunchCheckoutFlow(sku); // Perform the request

		UE_LOG(LogTemp, Warning, TEXT("OCULUS REQUEST SENT. Id: %d"), (int)requestId);
		if (requestId == invalidRequestID)
		{
			OnFailure.Broadcast();
		}
		else // Start polling messages
		{
			FAutoDeleteAsyncTask<FCallbackMessagePoller>* MessagePollTask = new FAutoDeleteAsyncTask<FCallbackMessagePoller>(MessageType, &UserIAPCheckCompleteDelegate);
			MessagePollTask->StartBackgroundTask();
		}
	}
	else
	{
		log("OCULUS PLATFORM UNINITIALIZED");
		OnFailure.Broadcast();
	}

}


void UOculusIAPCallbackProxy::OnUserIAPCheckCompleteDelegate(const ovrMessageHandle ReceivedMessage)
{

	UE_LOG(LogTemp, Warning, TEXT("ReceivedMessageType=%s"), ANSI_TO_TCHAR(ovrMessageType_ToString(ovr_Message_GetType(ReceivedMessage))));

	if (ReceivedMessage == nullptr)
	{
		log("IAP polling timeout");
		OnTimeout.Broadcast();
	}
	else if ( ovr_Message_IsError(ReceivedMessage) )
	{
		UE_LOG(LogTemp, Warning, TEXT("Oculus IAP returned error. Error=%s"), ovr_Error_GetMessage(ovr_Message_GetError(ReceivedMessage)));
		OnFailure.Broadcast();
	}
	else
	{
		log("IAP Check successful!");

		bool bUserHasPurchasedItem = false;
		bool bOutputAlreadyBroadcasted = false;
		ovrPurchaseArrayHandle UserPurchases;

		switch (ovr_Message_GetType(ReceivedMessage))
		{
		case ovrMessage_IAP_GetViewerPurchases:

			UserPurchases = ovr_Message_GetPurchaseArray(ReceivedMessage);

			UE_LOG(LogTemp, Warning, TEXT("Seeking sku=%s"), *this->Targetsku);

			for (int i = 0; i < ovr_PurchaseArray_GetSize(UserPurchases); i++) 
			{
				UE_LOG(LogTemp, Warning, TEXT("Found sku=%s"), ANSI_TO_TCHAR(ovr_Purchase_GetSKU(ovr_PurchaseArray_GetElement(UserPurchases, i))));

				if ( this->Targetsku == ovr_Purchase_GetSKU(ovr_PurchaseArray_GetElement(UserPurchases, i)) )
				{
					log("User IAP entitlement confirmed");
					if (!bOutputAlreadyBroadcasted)
					{
						OnSuccess.Broadcast();
						bOutputAlreadyBroadcasted = true;
					}
					break;
				}
			}

			log("User purchase not found");
			if (!bOutputAlreadyBroadcasted)
			{
				OnFailure.Broadcast();
				bOutputAlreadyBroadcasted = true;
			}
			break;

		case ovrMessage_IAP_GetProductsBySKU:

			log("product acquired from list.. ?? (partially implemented)");
			if (!bOutputAlreadyBroadcasted)
			{
				OnSuccess.Broadcast();
				bOutputAlreadyBroadcasted = true;
			}
			break;

		case ovrMessage_IAP_LaunchCheckoutFlow:

			log("Checkout successfully confirmed");
			if (!bOutputAlreadyBroadcasted)
			{
				OnSuccess.Broadcast();
				bOutputAlreadyBroadcasted = true;
			}
			break;

		default:
			break;
		}
	}
}
