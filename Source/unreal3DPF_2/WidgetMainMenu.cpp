// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetMainMenu.h"
#include "Kismet/KismetSystemLibrary.h" // QuitGame ����
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h" 

void UWidgetMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
		
	if (TitleAnimation != nullptr)
	{
		// Ÿ��Ʋȭ�� �����ִϸ��̼� ���
		PlayAnimation(TitleAnimation);
	}

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance && MyGameInstance->bTotitle == false)
	{
		MyGameInstance->PlayBGM(MyGameInstance->BGMcue);
	}	

	if (MyGameInstance->BGMcue != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BGM not null"));
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BGM null"));
	}

	// ��ưŬ���� Ŀ�����Լ��� ȣ���Ҽ��ְ� ���ε�����(��������Ʈ)
	BtnStartGame->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnClickBtnStart);
	BtnOption->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnClickBtnOption);
	BtnQuit->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnClickBtnQuit);
}

void UWidgetMainMenu::OnClickBtnStart()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance)
	{
		// ĳ���� ���� ������ �̵�		
		//FLatentActionInfo info;
		//UGameplayStatics::LoadStreamLevel(GetWorld(), FName(MyGameInstance->levelnameSelect), true, true, info);
		UGameplayStatics::OpenLevel(GetWorld(), FName(MyGameInstance->levelnameSelect));
	}
}

void UWidgetMainMenu::OnClickBtnOption()
{
	// ������ ����� ȭ�鿡 ������
	if (OptionWidget != nullptr)
	{
		CreateWidget(GetWorld(), OptionWidget)->AddToViewport();		
	}
}

void UWidgetMainMenu::OnClickBtnQuit()
{
	// ��������	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

