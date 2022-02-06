// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h" // QuitGame ����
#include "Kismet/GameplayStatics.h"	// OpenLevle ����
#include "Components/Button.h"
#include "WidgetGameOver.h"

void UWidgetGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	if (GameOverAni != nullptr)
	{
		// Ÿ��Ʋȭ�� �����ִϸ��̼� ���
		PlayAnimation(GameOverAni);
	}

	// ��ưŬ���� Ŀ�����Լ��� ȣ���Ҽ��ְ� ���ε�����(��������Ʈ)
	btnRetry->OnClicked.AddDynamic(this, &UWidgetGameOver::OnClickbtnRetry);
	btnExit->OnClicked.AddDynamic(this, &UWidgetGameOver::OnClickbtnExit);
}

void UWidgetGameOver::OnClickbtnRetry()
{
	// Game �Է¸��
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());

	// ���� �����
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UWidgetGameOver::OnClickbtnExit()
{
	// ��������	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
