// Fill out your copyright notice in the Description page of Project Settings.

#include "WidgetMainMenu.h"
#include "Kismet/KismetSystemLibrary.h" // QuitGame 포함
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h" 

void UWidgetMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
		
	if (TitleAnimation != nullptr)
	{
		// 타이틀화면 위젯애니메이션 재생
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

	// 버튼클릭시 커스텀함수를 호출할수있게 바인딩해줌(델리게이트)
	BtnStartGame->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnClickBtnStart);
	BtnOption->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnClickBtnOption);
	BtnQuit->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnClickBtnQuit);
}

void UWidgetMainMenu::OnClickBtnStart()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance)
	{
		// 캐릭터 선택 레벨로 이동		
		//FLatentActionInfo info;
		//UGameplayStatics::LoadStreamLevel(GetWorld(), FName(MyGameInstance->levelnameSelect), true, true, info);
		UGameplayStatics::OpenLevel(GetWorld(), FName(MyGameInstance->levelnameSelect));
	}
}

void UWidgetMainMenu::OnClickBtnOption()
{
	// 위젯을 만들고 화면에 보여줌
	if (OptionWidget != nullptr)
	{
		CreateWidget(GetWorld(), OptionWidget)->AddToViewport();		
	}
}

void UWidgetMainMenu::OnClickBtnQuit()
{
	// 게임종료	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

