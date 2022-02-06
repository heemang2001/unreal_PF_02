// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "GM_Select.h"

void AGM_Select::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		// 마우스 커서를 보이게함
		PlayerController->bShowMouseCursor = true;
	}

	// 위젯을 만들고 화면에 보여줌
	if (SelectWidget != nullptr)
	{
		CurWidget = CreateWidget(GetWorld(), SelectWidget);
		CurWidget->AddToViewport();
	}
}