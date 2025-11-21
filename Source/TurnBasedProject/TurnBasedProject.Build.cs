// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class 	TurnBasedProject : ModuleRules
{
	public TurnBasedProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"GameplayAbilities", 
			"GameplayTasks", 
			"GameplayTags",
			"EnhancedInput",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TurnBasedProject",
			"TurnBasedProject/Variant_Platforming",
			"TurnBasedProject/Variant_Platforming/Animation",
			"TurnBasedProject/Variant_Combat",
			"TurnBasedProject/Variant_Combat/AI",
			"TurnBasedProject/Variant_Combat/Animation",
			"TurnBasedProject/Variant_Combat/Gameplay",
			"TurnBasedProject/Variant_Combat/Interfaces",
			"TurnBasedProject/Variant_Combat/UI",
			"TurnBasedProject/Variant_SideScrolling",
			"TurnBasedProject/Variant_SideScrolling/AI",
			"TurnBasedProject/Variant_SideScrolling/Gameplay",
			"TurnBasedProject/Variant_SideScrolling/Interfaces",
			"TurnBasedProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
