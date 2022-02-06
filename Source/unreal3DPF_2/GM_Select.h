// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_Select.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API AGM_Select : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SelectWidget;

	UPROPERTY()
	class UUserWidget* CurWidget;
};
