// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/AudioComponent.h"
#include "Sound/SoundClass.h"

UAudioComponent* UMyGameInstance::PlayBGM(USoundBase* soundcue)
{	
	// 사운드큐 재생				
	return UGameplayStatics::SpawnSound2D(this, soundcue, 1.0f, 1.0f, 0.0f, nullptr, true, false);
}

void UMyGameInstance::SetOption(FStruct_Option curOption)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::SetOption"));

	// 배경음악이 체크되어있으면
	if (curOption.bMusic)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_BGM.SC_BGM"), NULL, LOAD_None, NULL);

		if (tSC != nullptr)
		{
			// 배경음악 볼륨을 켬
			UE_LOG(LogTemp, Warning, TEXT("tSC->Properties.Volume = 1.0f"));
			tSC->Properties.Volume = 1.0f;		
			bBGM = true;
		}		
	}

	// 배경음악 체크해제하면
	else if(!curOption.bMusic)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_BGM.SC_BGM"), NULL, LOAD_None, NULL);

		// 배경음악 볼륨을 끔
		// Volume을 0으로 하면 완전히꺼짐
		if (tSC != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("tSC->Properties.Volume = 0.001f"));
			tSC->Properties.Volume = 0.001f;				
			bBGM = false;
		}
	}

	// 효과음이 체크되어있으면
	if (curOption.bSound)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_SFX.SC_SFX"), NULL, LOAD_None, NULL);

		// 효과음 킴
		if (tSC != nullptr)
		{			
			tSC->Properties.Volume = 1.0f;
			bSound = true;
		}
	}

	else if (!curOption.bSound)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_SFX.SC_SFX"), NULL, LOAD_None, NULL);

		// 효과음 끔
		if (tSC != nullptr)
		{			
			tSC->Properties.Volume = 0.001f;
			bSound = false;
		}
	}
}

void UMyGameInstance::GetOption()
{

}

void UMyGameInstance::SetbTotitle(bool bCheck)
{
	bTotitle = bCheck;
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init()"));

	// 배경음악 가져옴
	BGMcue = LoadObject<USoundBase>(nullptr, TEXT("/Game/Assets/Sounds/MySound/BGM_KingKnight"), NULL, LOAD_None, NULL);

	// 게임오버 효과음 가져옴
	GameOvercue = LoadObject<USoundBase>(nullptr, TEXT("/Game/Assets/Sounds/MySound/GameOverBGM"), NULL, LOAD_None, NULL);

	// 레벨이름 가져옴
	levelnameTitle = FName(TEXT("levelMainMenu"));
	levelnameSelect = FName(TEXT("levelSelect"));	
	levelnamePlayGame = FName(TEXT("levelPlayGame_1"));
	levelnamePlayGame_0 = FName(TEXT("levelPlayGame_0"));
	curCharacterNum = 0;
	curCharacterPath = TEXT("/Game/Blueprints/BP_Warrior");	
}