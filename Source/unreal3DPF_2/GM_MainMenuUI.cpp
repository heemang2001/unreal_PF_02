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
		// 마우스 커서를 보이게함
		PlayerController->bShowMouseCursor = true;
	}

	// 위젯을 만들고 화면에 보여줌
	if (MainMenuWidget != nullptr)
	{
		CurWidget = CreateWidget(GetWorld(), MainMenuWidget);
		CurWidget->AddToViewport();
	}

	// TargetActor == tagMainCamera 태그를 가진 액터를 가져옴 (카메라)
	TArray<AActor*> TargetActor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("tagMainCamera")), TargetActor);

	if (TargetActor[0] != nullptr)
	{
		// TargetActor를 가져왔다면 ACameraAcotor로 캐스팅
		ACameraActor* camera = Cast<ACameraActor>(TargetActor[0]);

		// ACameraAcotor로 캐스팅 성공시
		if (camera != nullptr)
		{
			// 화면을 camera가 보고있는 화면으로 보여줌
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(camera);
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString("CameraTest"));
		}
	}
}
