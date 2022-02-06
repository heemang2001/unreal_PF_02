// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "GM_Select.h"

void AGM_Select::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		// ���콺 Ŀ���� ���̰���
		PlayerController->bShowMouseCursor = true;
	}

	// ������ ����� ȭ�鿡 ������
	if (SelectWidget != nullptr)
	{
		CurWidget = CreateWidget(GetWorld(), SelectWidget);
		CurWidget->AddToViewport();
	}
}