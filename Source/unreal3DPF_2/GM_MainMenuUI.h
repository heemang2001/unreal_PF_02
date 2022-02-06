// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API AGM_MainMenuUI : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainMenuWidget;

	UPROPERTY()
	class UUserWidget* CurWidget;	
};
