// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "WidgetGameUI.h"



void UWidgetGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("UWidgetGameUI C++ NativeConstruct"));

	// 월드에 있는 FindClassType형인 액터 받아오기
	AActor* tempActor = UGameplayStatics::GetActorOfClass(GetWorld(), FindClassType);

	if (tempActor)
	{
		AMyCharacter* MyActor = Cast<AMyCharacter>(tempActor);
		
		UE_LOG(LogTemp, Warning, TEXT("TEST hp : %f"), MyActor->HP);
	}

	// 유저 HP바 갱신
	Update_UserHpBar();	

	// 보스 HP바 숨김
	Invisible_BossHpBar();
}

void UWidgetGameUI::Visible_BossHpBar()
{
	// 보스 HP바 보여줌
	txtBossName->SetVisibility(ESlateVisibility::Visible);
	pbBossHPbar->SetVisibility(ESlateVisibility::Visible);
}

void UWidgetGameUI::Invisible_BossHpBar()
{
	// 보스 HP바 숨김
	txtBossName->SetVisibility(ESlateVisibility::Hidden);
	pbBossHPbar->SetVisibility(ESlateVisibility::Hidden);
}
