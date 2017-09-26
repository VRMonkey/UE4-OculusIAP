// All rights complied to VRMonkey

#include "OculusIAP.h"
#include "OculusIAPBPLibrary.h"


/*
Checks wether the user is entitled:
as downloaded the game through the proper means, and, if paid, owns it
@return bIsViewerEntitled
*/
UOculusIAPCallbackProxy* UOculusIAPBPLibrary::GetIAPEntitlement(FString ItemSKU) {

	UOculusIAPCallbackProxy* Proxy = NewObject<UOculusIAPCallbackProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);

	const char* sku = TCHAR_TO_ANSI(*ItemSKU);
	Proxy->VerifyIAPEntitlement(sku);

	return Proxy;
}

/*
Fetches the server for the given sku's price. Returns failure if wrong sku code or response polling failure
@return price in dollars
*/
void UOculusIAPBPLibrary::FetchIAPPrice(FString ItemSKU, float& Price, TEnumAsByte<EOculusIAPCheckResult::Type>& OutExec) {

	UOculusIAPCallbackProxy* Proxy = NewObject<UOculusIAPCallbackProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);

	const char* sku[] = { TCHAR_TO_ANSI(*ItemSKU) };
	Proxy->FetchIAPPrice(sku);


}



UOculusIAPCallbackProxy* UOculusIAPBPLibrary::LaunchStoreCheckout(FString ItemSKU) {

	UOculusIAPCallbackProxy* Proxy = NewObject<UOculusIAPCallbackProxy>();
	Proxy->SetFlags(RF_StrongRefOnFrame);

	const char* sku = TCHAR_TO_ANSI(*ItemSKU);
	Proxy->LaunchStoreCheckout(sku);

	return Proxy;

}