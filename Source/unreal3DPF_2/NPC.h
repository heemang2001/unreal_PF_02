// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interact.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "NPC.generated.h"

UCLASS()
class UNREAL3DPF_2_API ANPC : public AActor, public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 인터페이스 함수
	UFUNCTION(BlueprintImplementableEvent, Category = "Interface")
	void ActivateDialogue() ;

public:
	UPROPERTY()
	UTextRenderComponent* TextRender123;

};
