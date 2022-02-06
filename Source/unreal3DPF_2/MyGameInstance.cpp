// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/AudioComponent.h"
#include "Sound/SoundClass.h"

UAudioComponent* UMyGameInstance::PlayBGM(USoundBase* soundcue)
{	
	// ����ť ���				
	return UGameplayStatics::SpawnSound2D(this, soundcue, 1.0f, 1.0f, 0.0f, nullptr, true, false);
}

void UMyGameInstance::SetOption(FStruct_Option curOption)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::SetOption"));

	// ��������� üũ�Ǿ�������
	if (curOption.bMusic)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_BGM.SC_BGM"), NULL, LOAD_None, NULL);

		if (tSC != nullptr)
		{
			// ������� ������ ��
			UE_LOG(LogTemp, Warning, TEXT("tSC->Properties.Volume = 1.0f"));
			tSC->Properties.Volume = 1.0f;		
			bBGM = true;
		}		
	}

	// ������� üũ�����ϸ�
	else if(!curOption.bMusic)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_BGM.SC_BGM"), NULL, LOAD_None, NULL);

		// ������� ������ ��
		// Volume�� 0���� �ϸ� ����������
		if (tSC != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("tSC->Properties.Volume = 0.001f"));
			tSC->Properties.Volume = 0.001f;				
			bBGM = false;
		}
	}

	// ȿ������ üũ�Ǿ�������
	if (curOption.bSound)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_SFX.SC_SFX"), NULL, LOAD_None, NULL);

		// ȿ���� Ŵ
		if (tSC != nullptr)
		{			
			tSC->Properties.Volume = 1.0f;
			bSound = true;
		}
	}

	else if (!curOption.bSound)
	{
		USoundClass* tSC = LoadObject<USoundClass>(nullptr, TEXT("/Game/Assets/Sounds/MySound/SC_SFX.SC_SFX"), NULL, LOAD_None, NULL);

		// ȿ���� ��
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

	// ������� ������
	BGMcue = LoadObject<USoundBase>(nullptr, TEXT("/Game/Assets/Sounds/MySound/BGM_KingKnight"), NULL, LOAD_None, NULL);

	// ���ӿ��� ȿ���� ������
	GameOvercue = LoadObject<USoundBase>(nullptr, TEXT("/Game/Assets/Sounds/MySound/GameOverBGM"), NULL, LOAD_None, NULL);

	// �����̸� ������
	levelnameTitle = FName(TEXT("levelMainMenu"));
	levelnameSelect = FName(TEXT("levelSelect"));	
	levelnamePlayGame = FName(TEXT("levelPlayGame_1"));
	levelnamePlayGame_0 = FName(TEXT("levelPlayGame_0"));
	curCharacterNum = 0;
	curCharacterPath = TEXT("/Game/Blueprints/BP_Warrior");	
}