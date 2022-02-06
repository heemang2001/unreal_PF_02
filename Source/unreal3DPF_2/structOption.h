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

// Atomic�� ����ü�� �׻� �ϳ��� ������ ����ȭ���� �ǹ� ==> ����ü�� ������ ������ â���� ǥ�õǰ� ���� �����ϱ⸸ ���ϸ� Atomic
// BlueprintType�� �������Ʈ ��밡��
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
