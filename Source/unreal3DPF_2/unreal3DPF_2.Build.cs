// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class unreal3DPF_2 : ModuleRules
{
	public unreal3DPF_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// 나이아가라 사용위해 "Niagara" 추가 (.uproject에도 추가해야함)
		// UI 사용위해 "UMG" 추가
		// BT 사용하기 위해 "AIModule" 추가
		// Task 사용위해 "GameplayTasks" 추가
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "UMG", "AIModule", "GameplayTasks" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
