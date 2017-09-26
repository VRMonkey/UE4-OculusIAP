// All rights complied to VRMonkey

#pragma once

//#define OVRPL_DISABLED

#ifdef __ANDROID__
#include <jni.h>
#endif

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OVR_Platform.h"
#include "OnlineIdentityInterface.h"
#include "OnlineSubsystemOculus.h"
#include "OculusIAPCallbackProxy.h"
#include "CallbackMessagePoller.h"
#include "OculusIAPBPLibrary.generated.h"


UENUM()
namespace EOculusIAPCheckResult
{
	enum Type
	{
		Success,
		Fail,
		Timeout
	};
}


/**
*
*/
UCLASS()
class UOculusIAPBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Oculus|IAP")
		static UOculusIAPCallbackProxy* GetIAPEntitlement(FString ItemSKU);

	//UFUNCTION(BlueprintCallable, Category = "Oculus|IAP", Meta = (ExpandEnumAsExecs = "OutExec"))
	static void FetchIAPPrice(FString ItemSKU, float& Price, TEnumAsByte<EOculusIAPCheckResult::Type>& OutExec);

	UFUNCTION(BlueprintCallable, Category = "Oculus|IAP")
		static UOculusIAPCallbackProxy* LaunchStoreCheckout(FString ItemSKU);

};
