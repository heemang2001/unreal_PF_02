// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetGameClear.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API UWidgetGameClear : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override; // C++�� ���� ������	

public:
	UFUNCTION()
	void OnClickbtnTotitle();

	UFUNCTION()
	void OnClickbtnExit();

public:
	// BindWidgetAnim���� ����Ͱ� �������Ʈ ���� �ִϸ��̼� �̸��� ���ƾ��� ==> C++�� �����ѰͿ� �ڵ����� ���ε�
	// BindWidgetAnim�� ����, Transient�� ����ȭ�� ������������ ������ �������Ʈ �����Ͽ�����
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* GameClearAni;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* GameClearAni2;

	UPROPERTY(meta = (BindWidget))
	class UButton* btnTotitle;

	UPROPERTY(meta = (BindWidget))
	class UButton* btnExit;


};
