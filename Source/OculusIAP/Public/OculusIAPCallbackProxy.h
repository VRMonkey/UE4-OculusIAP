// All rights complied to VRMonkey

#pragma once

#ifdef __ANDROID__
#include <jni.h>
#endif

#include "UObject/NoExportTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "OVR_Platform.h"
#include "OnlineIdentityInterface.h"
#include "OnlineSubsystemOculus.h"
#include "Runtime/Core/Public/Delegates/DelegateSignatureImpl.inl"
#include "OculusIAPCallbackProxy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOculusIAPCheckResultDelegate);

DECLARE_DELEGATE_OneParam(FMessageDelegate, const ovrMessageHandle);

// Forward declarations
class FCallbackMessagePoller;

/**
* Proxy objects that send requests and stores messages from Oculus server
*
* At current implementaton this class receives every Oculus messages and treats them as soon as they are received. Messages 
* of different types than expected are discarded, and the polling continues until the correct one is returned or timeout is reached.
* Those messages may include ones from a parallel call as well as any other message sent and received through the OVRLibrary 
*/
UCLASS()
class UOculusIAPCallbackProxy : public UObject
{
	GENERATED_UCLASS_BODY()


public:

	// Called when there 
	UPROPERTY(BlueprintAssignable)
		FOculusIAPCheckResultDelegate OnSuccess;

	// Called when there is an unsuccessful check
	UPROPERTY(BlueprintAssignable)
		FOculusIAPCheckResultDelegate OnFailure;

	// Called when there is an unsuccessful check
	UPROPERTY(BlueprintAssignable)
		FOculusIAPCheckResultDelegate OnTimeout;
	
	void VerifyIAPEntitlement(const char* sku);

	void FetchIAPPrice(const char** sku);

	void LaunchStoreCheckout(const char* sku);


protected:

	FMessageDelegate UserIAPCheckCompleteDelegate;


private:

	FString Targetsku;

	// Delegate for VerifyIAPEntitlement.
	void OnUserIAPCheckCompleteDelegate(const ovrMessageHandle ReceivedMessage);

};
