// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h" // QuitGame 포함
#include "Kismet/GameplayStatics.h"	// OpenLevle 포함
#include "Components/Button.h"
#include "WidgetGameOver.h"

void UWidgetGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	if (GameOverAni != nullptr)
	{
		// 타이틀화면 위젯애니메이션 재생
		PlayAnimation(GameOverAni);
	}

	// 버튼클릭시 커스텀함수를 호출할수있게 바인딩해줌(델리게이트)
	btnRetry->OnClicked.AddDynamic(this, &UWidgetGameOver::OnClickbtnRetry);
	btnExit->OnClicked.AddDynamic(this, &UWidgetGameOver::OnClickbtnExit);
}

void UWidgetGameOver::OnClickbtnRetry()
{
	// Game 입력모드
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());

	// 레벨 재시작
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UWidgetGameOver::OnClickbtnExit()
{
	// 게임종료	
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
