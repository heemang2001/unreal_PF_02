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
	virtual void NativeConstruct() override; // C++의 위젯 생성자

public:
	// BindWidgetAnim으로 만든것과 블루프린트 위젯 애니메이션 이름이 같아야함 ==> C++에 선언한것에 자동으로 바인딩
	// BindWidgetAnim를 쓸때, Transient로 직렬화를 해제시켜주지 않으면 블루프린트 컴파일오류뜸
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
