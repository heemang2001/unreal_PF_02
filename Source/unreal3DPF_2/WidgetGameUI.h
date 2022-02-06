// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "WidgetGameUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API UWidgetGameUI : public UUserWidget
{
	GENERATED_BODY()

private:	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetHP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMyCharacter> FindClassType;

protected:
	virtual void NativeConstruct() override; // C++의 위젯 생성자

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* pbBossHPbar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txtBossName;

public:
	// BlueprintImplementableEvent : 구현부는 블루프린트에만 있음
	// 반환값 없으면 우클릭 이벤트호출가능 
	// 반환값 있으면 내 블루트린트 탭에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
	UImage* GetMyImage();

	// 유저 HP바 갱신
	// 구현부는 블루트린트에
	UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
	void Update_UserHpBar();

	// 보스 HP바 갱신
	// 구현부는 블루트린트에
	UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
	void Update_BossHpBar();

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Visible_BossHpBar();

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Invisible_BossHpBar();
};
