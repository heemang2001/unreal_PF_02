// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h" // QuitGame ����
#include "Kismet/GameplayStatics.h"	// OpenLevle ����
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "WidgetGameClear.h"

void UWidgetGameClear::NativeConstruct()
{
	Super::NativeConstruct();

	if (GameClearAni != nullptr)
	{
		// ����Ŭ���� �����ִϸ��̼� ���
		PlayAnimation(GameClearAni);
		PlayAnimation(GameClearAni2, 0.0f, 0,EUMGSequencePlayMode::PingPong, 1.0f, false);
	}

	// ��ưŬ���� Ŀ�����Լ��� ȣ���Ҽ��ְ� ���ε�����(��������Ʈ)
	btnTotitle->OnClicked.AddDynamic(this, &UWidgetGameClear::OnClickbtnTotitle);
	btnExit->OnClicked.AddDynamic(this, &UWidgetGameClear::OnClickbtnExit);
}

void UWidgetGameClear::OnClickbtnTotitle()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	// Ÿ��Ʋ�� ���� �ݺ���ٰ� ǥ�� (BGM ��ø����)
	MyGameInstance->SetbTotitle(true);

	// Game �Է¸��
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());

	// ���� ������ �̵�
	UGameplayStatics::OpenLevel(this, MyGameInstance->levelnameTitle, false);
}

void UWidgetGameClear::OnClickbtnExit()
{
	// ��������	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
