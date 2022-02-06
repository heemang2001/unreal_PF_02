// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class unreal3DPF_2 : ModuleRules
{
	public unreal3DPF_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// ���̾ư��� ������� "Niagara" �߰� (.uproject���� �߰��ؾ���)
		// UI ������� "UMG" �߰�
		// BT ����ϱ� ���� "AIModule" �߰�
		// Task ������� "GameplayTasks" �߰�
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Niagara", "UMG", "AIModule", "GameplayTasks" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
