// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WidgetGameUI.h"
#include "Misc/OutputDeviceNull.h"
#include "Animation/AnimMontage.h"

#include "MyCharacter.generated.h"

DECLARE_DELEGATE(testtest);

UCLASS()
class UNREAL3DPF_2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* MyCameraComponent;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* MyMesh;

protected:
	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void Rolling();

	UFUNCTION()
	void Run();

	UFUNCTION()
	void RunEnd();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Zoom(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void LMBDown();

	UFUNCTION(BlueprintCallable)
	void MyCharcterDeath();
			
	FORCEINLINE void LMBUp() { bLMBDown = false; }

	UFUNCTION()
	void MyOnBeginOverlap(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor,class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void MyOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	//UFUNCTION()
	//void StartJump();

	//UFUNCTION()
	//void StopJump();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RollingValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRolling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLMBDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bComboAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bArmWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bArmAniEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOverlapWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ComboCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Weapon")
	class USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Weapon")
	class UCapsuleComponent* WeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Interact")
	class UCapsuleComponent* InteractCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Anim")
	class UAnimMontage* victoryMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Anim")
	class UAnimMontage* deathMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Anim")
	class UAnimMontage* attackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Anim")
	class UAnimMontage* AnimUnArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Anim")
	class UAnimMontage* AnimArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Fx")
	class UNiagaraSystem* NS_Hit; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Fx")
	class USoundBase* SB_Hit;

	UPROPERTY(EditAnywhere, Category = "BlueprintClass")
	AActor* blueprintActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "UMG")
	UWidgetGameUI* UI_HP;

	FTimerHandle TimerHandle;

	// 애님 인스턴스를 가져옴
	UPROPERTY()
	UAnimInstance* Animinstance;

public:
	UFUNCTION()
	void Attack();

	// AnimNotify 호출함수
	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	// AnimNotify 호출함수
	UFUNCTION(BlueprintCallable)
	void AttackInputChecking();

	UFUNCTION(BlueprintCallable)
	void UnArmWeapon();

	UFUNCTION(BlueprintCallable)
	void ArmWeapon();
};
