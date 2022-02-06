// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class UNREAL3DPF_2_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	AActor* CameraWarrior;

	UPROPERTY(EditAnywhere)
	AActor* CameraMagician;	

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Camaras;

	UPROPERTY(EditAnywhere)
	int8 curIndex;

	UPROPERTY(EditAnywhere)
	float TimeToNextCameraChange;

public:
	UFUNCTION(BlueprintCallable)
	void testFunction();

	UFUNCTION(BlueprintCallable)
	void testFunction2();


};
