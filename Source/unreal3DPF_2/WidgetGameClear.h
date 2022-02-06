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
	virtual void NativeConstruct() override; // C++의 위젯 생성자	

public:
	UFUNCTION()
	void OnClickbtnTotitle();

	UFUNCTION()
	void OnClickbtnExit();

public:
	// BindWidgetAnim으로 만든것과 블루프린트 위젯 애니메이션 이름이 같아야함 ==> C++에 선언한것에 자동으로 바인딩
	// BindWidgetAnim를 쓸때, Transient로 직렬화를 해제시켜주지 않으면 블루프린트 컴파일오류뜸
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* GameClearAni;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* GameClearAni2;

	UPROPERTY(meta = (BindWidget))
	class UButton* btnTotitle;

	UPROPERTY(meta = (BindWidget))
	class UButton* btnExit;


};
