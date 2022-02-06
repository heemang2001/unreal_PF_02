// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyAIController.h"
#include "WidgetGameUI.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class UNREAL3DPF_2_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void EnemyDeath();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float EnemyHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float EnemyDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	FString EnemyName;

	// �ΰ����� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere)
	AMyAIController* AI_Enemy1;

	// ���� HP�� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "UMG")
	class UWidgetGameUI* UI_BossHP;

	// �ִ� �ν��Ͻ��� ������
	UPROPERTY()
	UAnimInstance* Animinstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Anim")
	class UAnimMontage* AnimEnemyDeath;

	//UPROPERTY(EditDefaultsOnly, Category = "AI")
	//TSubclassOf<AMyAIController> AI_Enemy;

private:
	float EnemyMaxHP;
};
