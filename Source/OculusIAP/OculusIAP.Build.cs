// All rights complied to VRMonkey

using UnrealBuildTool;

public class OculusIAP : ModuleRules
{
	public OculusIAP(ReadOnlyTargetRules Target) : base(Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"OculusIAP/Public"
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"OculusIAP/Private"
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
            {
                "LibOVRPlatform",
                "OnlineSubsystemOculus",
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
            {
                "Core",
                "CoreUObject",
                "InputCore",
                "Engine",
                "Slate",
                "SlateCore"
            }
			);
		
		DynamicallyLoadedModuleNames.AddRange(new string[]{	});
	}
}
