// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GMTEST.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API AGMTEST : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGMTEST();

public:
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	TSubclassOf<UUserWidget> WidgetUI;

	//UPROPERTY()
	//	class UUserWidget* CurWidget;
};
