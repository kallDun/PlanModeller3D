// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlanModeller3D : ModuleRules
{
	public PlanModeller3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "UMG", "Engine", "InputCore", "Json", "JsonUtilities", "ProceduralMeshComponent", "GeometryFramework", "GeometryScriptingEditor"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
