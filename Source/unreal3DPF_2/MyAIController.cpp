// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AMyAIController::AMyAIController()
{
	// [error - 75% 언리얼엔진 멈춤]
	//// 블랙보드
	//static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/EnemyAI/BBEnemy"));
	//if (BBObject.Succeeded())
	//{
	//	UE_LOG(LogTemp, Log, TEXT("BBObject.Succeeded()"));
	//	BBAsset = BBObject.Object;
	//}

	//// 비헤이비어 트리
	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/EnemyAI/BTEnemy"));
	//if (BTObject.Succeeded())
	//{
	//	UE_LOG(LogTemp, Log, TEXT("BTObject.Succeeded()"));
	//	BTAsset = BTObject.Object;
	//}
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// AI 실행
	RunAI();
}

void AMyAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		// 비헤이비어 트리 시작
		RunBehaviorTree(BTAsset);
	}
}

void AMyAIController::StopAI()
{
	UE_LOG(LogTemp, Log, TEXT("StopAI()"));			
	
	BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(GetBrainComponent());

	if (nullptr == BehaviorTreeComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("nullptr == BehaviorTreeComponent"));
		return;
	}

	// 비헤이비어 트리 멈춤
	UE_LOG(LogTemp, Log, TEXT("nullptr != BehaviorTreeComponent"));
	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
