// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

	void RunAI();
	void StopAI();

private:
	UPROPERTY(EditDefaultsOnly, Category = "MY_AI")
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, Category = "MY_AI")
	class UBlackboardData* BBAsset;

	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
};
