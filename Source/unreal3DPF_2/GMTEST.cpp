// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "GMTEST.h"

AGMTEST::AGMTEST()
{
	UE_LOG(LogTemp, Warning, TEXT("AGMTEST()"));

	// World가 존재하는지 확인하고 게임인스턴스를 불러와야함 
	// 안그러면 크래쉬뜸
	if (GetWorld())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

		ConstructorHelpers::FClassFinder<AMyCharacter> PlayerPawnClassFinder(*MyGameInstance->curCharacterPath);
		UE_LOG(LogTemp, Warning, TEXT("curPath : %s"), *MyGameInstance->curCharacterPath);

		if (PlayerPawnClassFinder.Class != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass Change!"));
			DefaultPawnClass = PlayerPawnClassFinder.Class;
		}
	}
}

void AGMTEST::BeginPlay()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	UE_LOG(LogTemp, Warning, TEXT("curindex : %d"), MyGameInstance->curCharacterNum);
}
