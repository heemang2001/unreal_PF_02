// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h" // QuitGame 포함
#include "Kismet/GameplayStatics.h"	// OpenLevle 포함
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "WidgetGameClear.h"

void UWidgetGameClear::NativeConstruct()
{
	Super::NativeConstruct();

	if (GameClearAni != nullptr)
	{
		// 게임클리어 위젯애니메이션 재생
		PlayAnimation(GameClearAni);
		PlayAnimation(GameClearAni2, 0.0f, 0,EUMGSequencePlayMode::PingPong, 1.0f, false);
	}

	// 버튼클릭시 커스텀함수를 호출할수있게 바인딩해줌(델리게이트)
	btnTotitle->OnClicked.AddDynamic(this, &UWidgetGameClear::OnClickbtnTotitle);
	btnExit->OnClicked.AddDynamic(this, &UWidgetGameClear::OnClickbtnExit);
}

void UWidgetGameClear::OnClickbtnTotitle()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	// 타이틀로 가서 반복됬다고 표시 (BGM 중첩방지)
	MyGameInstance->SetbTotitle(true);

	// Game 입력모드
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());

	// 메인 레벨로 이동
	UGameplayStatics::OpenLevel(this, MyGameInstance->levelnameTitle, false);
}

void UWidgetGameClear::OnClickbtnExit()
{
	// 게임종료	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
