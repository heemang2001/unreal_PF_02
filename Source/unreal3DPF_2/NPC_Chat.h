// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC_Chat.generated.h"

UCLASS()
class UNREAL3DPF_2_API ANPC_Chat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC_Chat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

// 구조체
USTRUCT(BlueprintType)
struct FStruct_NPC_Chat
{
public:

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NPC_Message_0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NPC_Message_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NPC_Message_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_00;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_01;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_11;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Player_Message_20;

};
