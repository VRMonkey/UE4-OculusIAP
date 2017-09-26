// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "OculusIAP.h"
#include "OculusIAPPrivatePCH.h"

#define LOCTEXT_NAMESPACE "FOculusIAPModule"

DEFINE_LOG_CATEGORY(OculusIAP);


void FOculusIAPModule::StartupModule()
{
	log("module started");	
}

void FOculusIAPModule::ShutdownModule()
{
	log("module shutdown");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOculusIAPModule, OculusIAP)