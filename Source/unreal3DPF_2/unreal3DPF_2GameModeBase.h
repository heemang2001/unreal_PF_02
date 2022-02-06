// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "unreal3DPF_2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API Aunreal3DPF_2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	Aunreal3DPF_2GameModeBase();

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> WidgetUI;

	UPROPERTY()
	class UUserWidget* CurWidget;
};
