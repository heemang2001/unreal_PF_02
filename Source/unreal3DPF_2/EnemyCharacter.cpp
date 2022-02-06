// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "Interact.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// tagEnemy 태그 추가
	Tags.Add("tagEnemy");
	
	// AI 컨트롤러 설정
	//AIControllerClass = AMyAIController::StaticClass();
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//static ConstructorHelpers::FObjectFinder<UClass> EnemyAIcontroller(TEXT("/Game/EnemyAI/BP_MyAIController.BP_MyAIController_C"));

	//if (EnemyAIcontroller.Succeeded())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("EnemyAIcontroller Not Null"));
	//	AI_Enemy1 = Cast<AMyAIController>(EnemyAIcontroller.Object);
	//}

	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("EnemyAIcontroller Null"));
	//}

	EnemyHP = EnemyMaxHP = 1.0;
	EnemyDamage = 0.1;
	EnemyName = TEXT("BOSSNAME");
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 애님 인스턴스를 가져옴
	Animinstance = GetMesh()->GetAnimInstance();

	UI_BossHP->Update_BossHpBar();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	EnemyHP -= Damage;

	UE_LOG(LogTemp, Log, TEXT("EnemyHP : %f"), EnemyHP);

	// 보스 HP바 갱신
	if (UI_BossHP)
	{
		UI_BossHP->Update_BossHpBar();
	}	

	if (EnemyHP <= 0)
	{
		EnemyDeath();
		return Damage;
	}

	return Damage;
}

// 보스가 죽으면
void AEnemyCharacter::EnemyDeath()
{
	UE_LOG(LogTemp, Log, TEXT("EnemyDeath()"));

	AI_Enemy1 = Cast<AMyAIController>(GetController());
		
	if (AI_Enemy1)
	{
		UE_LOG(LogTemp, Log, TEXT("AI_Enemy1 NOT NULL"));
				
		AI_Enemy1->StopAI();	// AI멈춤
		Animinstance->Montage_Play(AnimEnemyDeath);	// 죽는 애니메이션 재생			

		// 람다를 통한 Delay 구현
		FTimerHandle testTimerHandle;
		float Time = 1.5; // Time초 뒤
		GetWorld()->GetTimerManager().SetTimer(testTimerHandle, [&]()
		{
			// 보스 HP바 UI 지움
			UI_BossHP->RemoveFromParent();

			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
			if (MyGameInstance)
			{
				if (MyGameInstance->WidgetGameClear != nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("MyGameInstance->WidgetGameClear != nullptr"));

					// 플레이어 캐릭터를 가져옴
					AMyCharacter* Mycharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

					// 플레이어 승리모션 재생
					if (Mycharacter && Mycharacter->Animinstance && Mycharacter->victoryMontage)
					{
						Mycharacter->Animinstance->Montage_Play(Mycharacter->victoryMontage);
					}					

					// 위젯을 만들고 화면에 보여줌			
					CreateWidget(GetWorld(), MyGameInstance->WidgetGameClear)->AddToViewport();

					// UI 입력모드
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

					// 마우스 커서 보이게
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
				}

				else
				{
					UE_LOG(LogTemp, Log, TEXT("MyGameInstance->WidgetGameClear == nullptr"));
				}
			}

		}, Time, false); // 반복하려면 false를 true로 변경
	}

	//if (AI_Enemy != nullptr)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("AI_Enemy != nullptr"));
	//	AMyAIController* tempAI = Cast<AMyAIController>(AI_Enemy->ClassDefaultObject);
	//	tempAI->StopAI();
	//}
}

