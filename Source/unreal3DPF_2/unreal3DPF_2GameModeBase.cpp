// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "unreal3DPF_2GameModeBase.h"

Aunreal3DPF_2GameModeBase::Aunreal3DPF_2GameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("Aunreal3DPF_2GameModeBase()"));
	
	// World가 존재하는지 확인하고 게임인스턴스를 불러와야함 
	// 안그러면 크래쉬뜸
	if (GetWorld())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

		if (MyGameInstance)
		{
			ConstructorHelpers::FClassFinder<AMyCharacter> PlayerPawnClassFinder(*MyGameInstance->curCharacterPath);
			UE_LOG(LogTemp, Warning, TEXT("curPath : %s"), *MyGameInstance->curCharacterPath);

			if (PlayerPawnClassFinder.Class != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass Change!"));
				DefaultPawnClass = PlayerPawnClassFinder.Class;
			}
		}			
	}	
}

void Aunreal3DPF_2GameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	UE_LOG(LogTemp, Warning, TEXT("Aunreal3DPF_2GameModeBase::ChangeWidget()"));

	if (CurWidget != nullptr)
	{
		CurWidget->RemoveFromViewport();  // Before widget delete
		UE_LOG(LogTemp, Warning, TEXT("CurWidget->RemoveFromViewport()"));
		CurWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurWidget != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UI AddToViewport!"));
			CurWidget->AddToViewport(); // View current widget
		}
	}
}


void Aunreal3DPF_2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetUI)
	{
		ChangeWidget(WidgetUI);
	}	

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("curindex : %d"), MyGameInstance->curCharacterNum);
	}
}
