// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "WidgetGameUI.h"



void UWidgetGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("UWidgetGameUI C++ NativeConstruct"));

	// ���忡 �ִ� FindClassType���� ���� �޾ƿ���
	AActor* tempActor = UGameplayStatics::GetActorOfClass(GetWorld(), FindClassType);

	if (tempActor)
	{
		AMyCharacter* MyActor = Cast<AMyCharacter>(tempActor);
		
		UE_LOG(LogTemp, Warning, TEXT("TEST hp : %f"), MyActor->HP);
	}

	// ���� HP�� ����
	Update_UserHpBar();	

	// ���� HP�� ����
	Invisible_BossHpBar();
}

void UWidgetGameUI::Visible_BossHpBar()
{
	// ���� HP�� ������
	txtBossName->SetVisibility(ESlateVisibility::Visible);
	pbBossHPbar->SetVisibility(ESlateVisibility::Visible);
}

void UWidgetGameUI::Invisible_BossHpBar()
{
	// ���� HP�� ����
	txtBossName->SetVisibility(ESlateVisibility::Hidden);
	pbBossHPbar->SetVisibility(ESlateVisibility::Hidden);
}
