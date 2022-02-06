// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "structOption.generated.h"

UCLASS()
class UNREAL3DPF_2_API AstructOption : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AstructOption();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

// Atomic은 구조체가 항상 하나의 단위로 직렬화됨을 의미 ==> 구조체가 에디터 디테일 창에서 표시되고 수정 가능하기만 원하면 Atomic
// BlueprintType은 블루프린트 사용가능
USTRUCT(Atomic, BlueprintType)
struct FStruct_Option
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSound;		
};
