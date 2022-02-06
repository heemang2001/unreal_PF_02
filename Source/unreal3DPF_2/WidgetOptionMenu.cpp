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

	// üũ�ڽ� ���� �����;���
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	CBMusic->SetIsChecked(MyGameInstance->bBGM);
	CBSound->SetIsChecked(MyGameInstance->bSound);

	if (FadeAnimation != nullptr)
	{
		// �ɼǸ޴� �����ִϸ��̼� ���
		PlayAnimation(FadeAnimation);
	}

	// Back��ư ������
	BtnBack->OnClicked.AddDynamic(this, &UWidgetOptionMenu::OnClickBtnBack);

	// üũ�ڽ�(BGM, SOUND) ������
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
	// ���� üũ�ڽ� ���� ����
	FStruct_Option curOption;
	curOption.bMusic = CBMusic->IsChecked();
	curOption.bSound = CBSound->IsChecked();

	// ���� üũ�ڽ� ���� �����ν��Ͻ��� 
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	MyGameInstance->SetOption(curOption);
}

void UWidgetOptionMenu::OnClickBtnBack()
{
	// ����� ���� �����ν��Ͻ��� ������
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	// �ɼǸ޴� �����ִϸ��̼� �����
	PlayAnimation(FadeAnimation,0,1,EUMGSequencePlayMode::Reverse,1,false);
	
	FTimerHandle WaitHandle;
	float EndTime_FadeAnimation = FadeAnimation->GetEndTime(); // �ð�����

	// Ÿ�̸ӿ� ���ٸ� ���� Delay���
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	{
		// �ɼǸ޴� ������ �θ��������� ����
		RemoveFromParent();

	}), EndTime_FadeAnimation, false);	
}
