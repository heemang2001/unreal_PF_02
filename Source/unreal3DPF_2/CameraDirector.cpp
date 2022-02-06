// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "WidgetSelectMenu.h"
#include "MyGameInstance.h"
#include "CameraDirector.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	curIndex = 0;
	TimeToNextCameraChange = 1.0f;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();

	Camaras.Add(CameraWarrior);
	Camaras.Add(CameraMagician);

	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
	if (controller)
	{
		controller->SetViewTarget(Camaras[curIndex]);
	}	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Select 오른쪽 이동
void ACameraDirector::testFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("testFunction()"));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
		
	if (curIndex >= 1)
	{
		curIndex = 0;
	}

	else
	{
		curIndex++;
	}

	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
	if (controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("testFunction() IN"));
		controller->SetViewTargetWithBlend(Camaras[curIndex], TimeToNextCameraChange);
		MyGameInstance->curCharacterNum = curIndex;
	}
}

// Select 왼쪽 이동
void ACameraDirector::testFunction2()
{
	UE_LOG(LogTemp, Warning, TEXT("testFunction2()"));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (curIndex <= 0)
	{
		curIndex = 1;
	}

	else
	{
		curIndex--;
	}

	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
	if (controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("testFunction() IN"));
		controller->SetViewTargetWithBlend(Camaras[curIndex], TimeToNextCameraChange);
		MyGameInstance->curCharacterNum = curIndex;
	}
}

