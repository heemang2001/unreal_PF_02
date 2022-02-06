// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetOptionMenu.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h" 
#include "TimerManager.h" // FTimerDelegate

void UWidgetOptionMenu::NativeConstruct()
{
	Super::NativeConstruct();	

	// 체크박스 상태 가져와야함
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	CBMusic->SetIsChecked(MyGameInstance->bBGM);
	CBSound->SetIsChecked(MyGameInstance->bSound);

	if (FadeAnimation != nullptr)
	{
		// 옵션메뉴 위젯애니메이션 재생
		PlayAnimation(FadeAnimation);
	}

	// Back버튼 누를시
	BtnBack->OnClicked.AddDynamic(this, &UWidgetOptionMenu::OnClickBtnBack);

	// 체크박스(BGM, SOUND) 누를시
	CBMusic->OnCheckStateChanged.AddDynamic(this, &UWidgetOptionMenu::SetupOptionToInstance);
	CBSound->OnCheckStateChanged.AddDynamic(this, &UWidgetOptionMenu::SetupOptionToInstance);


	if (MyGameInstance->bBGM)
	{
		CBMusic->SetCheckedState(ECheckBoxState::Checked);
	}

	else if (!MyGameInstance->bBGM)
	{
		CBMusic->SetCheckedState(ECheckBoxState::Unchecked);
	}

	if (MyGameInstance->bSound)
	{
		CBSound->SetCheckedState(ECheckBoxState::Checked);
	}

	else if (!MyGameInstance->bSound)
	{
		CBSound->SetCheckedState(ECheckBoxState::Unchecked);
	}

	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance->bBGM : %d "), MyGameInstance->bBGM);
}

void UWidgetOptionMenu::SetupOptionToInstance(bool bIsChecked)
{
	// 현재 체크박스 상태 저장
	FStruct_Option curOption;
	curOption.bMusic = CBMusic->IsChecked();
	curOption.bSound = CBSound->IsChecked();

	// 현재 체크박스 상태 게임인스턴스로 
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	MyGameInstance->SetOption(curOption);
}

void UWidgetOptionMenu::OnClickBtnBack()
{
	// 사용자 정의 게임인스턴스를 가져옴
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	// 옵션메뉴 위젯애니메이션 역재생
	PlayAnimation(FadeAnimation,0,1,EUMGSequencePlayMode::Reverse,1,false);
	
	FTimerHandle WaitHandle;
	float EndTime_FadeAnimation = FadeAnimation->GetEndTime(); // 시간설정

	// 타이머와 람다를 통한 Delay기능
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	{
		// 옵션메뉴 위젯을 부모위젯에서 제거
		RemoveFromParent();

	}), EndTime_FadeAnimation, false);	
}
