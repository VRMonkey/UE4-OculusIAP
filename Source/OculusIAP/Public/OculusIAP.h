// All rights complied to VRMonkey

/**
@author Rodolfo Cortese
@version 1.1 17/05/30
*/

#pragma once

#include "ModuleManager.h"

#define log(text) UE_LOG(OculusIAP, Warning, TEXT(text));

DECLARE_LOG_CATEGORY_EXTERN(OculusIAP, Log, All);


class FOculusIAPModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};