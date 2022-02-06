// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API UWidgetMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override; // C++�� ���� ������

public:
	// BindWidgetAnim���� ����Ͱ� �������Ʈ ���� �ִϸ��̼� �̸��� ���ƾ��� ==> C++�� �����ѰͿ� �ڵ����� ���ε�
	// BindWidgetAnim�� ����, Transient�� ����ȭ�� ������������ ������ �������Ʈ �����Ͽ�����
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* TitleAnimation;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnStartGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnOption;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnQuit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OptionWidget;

public:
	UFUNCTION(BlueprintCallable)
	void OnClickBtnStart();

	UFUNCTION()
	void OnClickBtnOption();

	UFUNCTION()
	void OnClickBtnQuit();
};
