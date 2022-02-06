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
	virtual void NativeConstruct() override; // C++�� ���� ������

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* pbBossHPbar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txtBossName;

public:
	// BlueprintImplementableEvent : �����δ� �������Ʈ���� ����
	// ��ȯ�� ������ ��Ŭ�� �̺�Ʈȣ�Ⱑ�� 
	// ��ȯ�� ������ �� ���Ʈ��Ʈ �ǿ��� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
	UImage* GetMyImage();

	// ���� HP�� ����
	// �����δ� ���Ʈ��Ʈ��
	UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
	void Update_UserHpBar();

	// ���� HP�� ����
	// �����δ� ���Ʈ��Ʈ��
	UFUNCTION(BlueprintImplementableEvent, Category = "UMG")
	void Update_BossHpBar();

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Visible_BossHpBar();

	UFUNCTION(BlueprintCallable, Category = "UMG")
	void Invisible_BossHpBar();
};
