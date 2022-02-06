// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "structOption.h"
#include "WidgetOptionMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API UWidgetOptionMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override; // C++의 위젯 생성자

public:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeAnimation;
	
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CBMusic;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CBSound;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnBack;

	UPROPERTY(EditAnywhere)
	FStruct_Option CurrentOptions;

public:
	UFUNCTION()
	void SetupOptionToInstance(bool bIsChecked);

	UFUNCTION()
	void OnClickBtnBack();
};
