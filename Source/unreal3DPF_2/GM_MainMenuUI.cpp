// Fill out your copyright notice in the Description page of Project Settings.

#include "GM_MainMenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Templates/Casts.h"
#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"

void AGM_MainMenuUI::BeginPlay()
{
	Super::BeginPlay();
		
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		// ���콺 Ŀ���� ���̰���
		PlayerController->bShowMouseCursor = true;
	}

	// ������ ����� ȭ�鿡 ������
	if (MainMenuWidget != nullptr)
	{
		CurWidget = CreateWidget(GetWorld(), MainMenuWidget);
		CurWidget->AddToViewport();
	}

	// TargetActor == tagMainCamera �±׸� ���� ���͸� ������ (ī�޶�)
	TArray<AActor*> TargetActor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("tagMainCamera")), TargetActor);

	if (TargetActor[0] != nullptr)
	{
		// TargetActor�� �����Դٸ� ACameraAcotor�� ĳ����
		ACameraActor* camera = Cast<ACameraActor>(TargetActor[0]);

		// ACameraAcotor�� ĳ���� ������
		if (camera != nullptr)
		{
			// ȭ���� camera�� �����ִ� ȭ������ ������
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(camera);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("CameraTest"));
		}
	}
}
