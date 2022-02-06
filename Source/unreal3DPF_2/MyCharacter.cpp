// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Blueprint/UserWidget.h"
#include "Engine/EngineTypes.h"
#include "MyGameInstance.h"
#include "NPC.h"
#include "TimerManager.h"
#include "Interact.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#define SPEED_RUN 600.0f
#define SPEED_WALK 222.0f

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// tagPlayer �±� �߰�
	Tags.Add("tagPlayer");

	// ü��
	HP = 0.9f;

	// ������ �ӵ�
	RollingValue = 2500.f;
	bRolling = false;

	// �ȱ�, �޸��� �ӷ�
	Speed = SPEED_WALK;

	// ī�޶��� �Ÿ�, �ӷ�
	ZoomValue = 333.0f;
	ZoomSpeed = 15.0f;

	// ���� ���� ��ġ	
	FName weaponSocket(TEXT("WeaponSocket"));

	// ĳ���Ͱ� ī�޶��� ȸ���� ���� ȸ������ �ʵ��� �Ѵ�.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ĳ������ �̵�
	GetCharacterMovement()->bOrientRotationToMovement = true; // �ڵ������� ĳ������ �̵������� �����̴� �������� ������
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); //ĳ������ �����Ʈ�� �����ϴ� �ڵ��, ĳ���͸� �̵���Ű�� ���� �̵� ����� ���� ĳ������ ������ �ٸ��� ĳ���͸� �̵� �������� �ʴ� 640���� ȸ�� �ӵ��� ȸ����Ų���� �̵�
	GetCharacterMovement()->bConstrainToPlane = true; // �̵��� ������� ���� // ���(�׺���̼� �޽�)
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // ĳ������ ��ġ�� ����� ��� ���¶�� ����� ������� �ٿ��� ����
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	GetCharacterMovement()->JumpZVelocity = 600.f;

	// ��������
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = ZoomValue;
	CameraBoom->bUsePawnControlRotation = true;

	// ī�޶�
	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCharacterCamera"));
	MyCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MyCameraComponent->bUsePawnControlRotation = false;

	// ����
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), weaponSocket);

	// ���� �浹ü
	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(Weapon);
	WeaponCollision->SetGenerateOverlapEvents(true); // overlap �̺�Ʈ�� �������ؼ� ����	

	// ��ȣ�ۿ� �浹ü
	InteractCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(RootComponent);
	InteractCollision->SetGenerateOverlapEvents(true); // overlap �̺�Ʈ�� �������ؼ� ����	
	InteractCollision->SetCapsuleRadius(111.1f, true);
	InteractCollision->SetCapsuleSize(111.1f, true);

	WeaponDamage = 10.0f;
	bLMBDown = false;
	bAttacking = false;
	bComboAttack = false;
	bArmWeapon = true;
	ComboCount = 0;
	bArmAniEnd = true;
	bOverlapWeapon = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �ִ� �ν��Ͻ��� ������
	Animinstance = GetMesh()->GetAnimInstance();

	// ���̳��� ��������Ʈ ���ε� // ������ �Լ� ����
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::MyOnBeginOverlap);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::MyOverlapEnd);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("%d"), bAttacking);
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::SanitizeFloat(ZoomValue));
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �����¿� �̵� 
	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	// �޸���
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::RunEnd);

	// ����
	//InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	//InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	// ����
	InputComponent->BindAction("Attack01", IE_Pressed, this, &AMyCharacter::LMBDown);
	InputComponent->BindAction("Attack01", IE_Released, this, &AMyCharacter::LMBUp);

	// ����
	InputComponent->BindAction("Rolling", IE_Pressed, this, &AMyCharacter::Rolling);

	// ��ȣ�ۿ�(NPC��)
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);

	// ī�޶� ����ȸ��
	InputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	// ī�޶� �ܱ��
	InputComponent->BindAxis("Zoom", this, &AMyCharacter::Zoom);

}

// E��ư ����
void AMyCharacter::Interact()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AActor::StaticClass());	// ��ȣ�ۿ� �浹ü�� ��ģ Actor ��ȯ

	UE_LOG(LogTemp, Warning, TEXT("Interact()"));

	for (auto overlapedActor : Result)
	{
		// �� ���Ͱ� �������̽��� �����Ǿ��ִ°�?
		bool bInterface = UKismetSystemLibrary::DoesImplementInterface(overlapedActor, UInteract::StaticClass());

		if (bInterface == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("bInterface == true"));
			ANPC* tempNPC = Cast<ANPC>(overlapedActor);

			if (tempNPC)
			{
				tempNPC->ActivateDialogue();
			}
		}
	}
}

void AMyCharacter::MoveForward(float AxisValue)
{
	if (!bAttacking && bArmAniEnd)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);

		// ��Ʈ�ѷ� ���� Z�� �����θ� �̵��ϰ���
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	if (!bAttacking && bArmAniEnd)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);

		// ��Ʈ�ѷ� ���� Z�� �����θ� �̵��ϰ���
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMyCharacter::Rolling()
{
	if (!bRolling)
	{
		bRolling = true;
		FRotator Direction = GetActorRotation();
		FVector vecDirection = Direction.Vector() * RollingValue;

		LaunchCharacter(vecDirection, false, false);
	}
}

void AMyCharacter::Run()
{
	if (bArmWeapon)
	{
		UnArmWeapon();
	}

	Speed = SPEED_RUN;
	bRun = true;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AMyCharacter::RunEnd()
{
	Speed = SPEED_WALK;
	bRun = false;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AMyCharacter::Zoom(float AxisValue)
{
	//UE_LOG(LogTemp, Log, TEXT("test : %f"), AxisValue);
	CameraBoom->TargetArmLength -= (ZoomSpeed * AxisValue);

	// �� ����
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, 265.0f, 800.0f);
}

void AMyCharacter::LMBDown()
{
	UE_LOG(LogTemp, Warning, TEXT("LMBDown()"));
	bLMBDown = true;

	if (bArmWeapon == false && !(Animinstance->Montage_IsPlaying(AnimArm)))
	{
		ArmWeapon();
	}

	// �������� �ƴҶ��� �����Լ� ȣ��
	else if (bAttacking == false && bArmWeapon == true && bArmAniEnd)
	{
		Attack();
	}

	// �������϶�
	else if (bAttacking == true && bArmWeapon == true && bArmAniEnd)
	{
		bComboAttack = true;
	}
}

void AMyCharacter::MyCharcterDeath()
{
	// �״� ��� ���
	Animinstance->Montage_Play(deathMontage);	

	// ���ٸ� ���� Delay ����
	FTimerHandle testTimerHandle;
	float Time = 2.0f; // Time�� ��
	GetWorld()->GetTimerManager().SetTimer(testTimerHandle, [&]()
		{
			// �ڵ� ����
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

			if (MyGameInstance)
			{
				UE_LOG(LogTemp, Warning, TEXT("MyGameInstance != nullptr"));

				if (MyGameInstance->WidgetGameover != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("MyGameInstance->WidgetGameover != nullptr"));

					// ������ ����� ȭ�鿡 ������			
					CreateWidget(GetWorld(), MyGameInstance->WidgetGameover)->AddToViewport();

					// ȿ���� ���
					MyGameInstance->PlayBGM(MyGameInstance->GameOvercue);

					// UI �Է¸��
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

					// ���콺 Ŀ�� ���̰�
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

					// ���� �Ͻ�����
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(true);
				}
			}

			// TimerHandle �ʱ�ȭ
			//GetWorld()->GetTimerManager().ClearTimer(testTimerHandle);
		}, Time, false);	// �ݺ��Ϸ��� false�� true�� ����
}

void AMyCharacter::Attack()
{
	if (bArmWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack()"));
		bLMBDown = true;

		// (������) �ִ��ν��Ͻ��� ���ø�Ÿ�ְ� ���� �ϳ��� nullptr�̸� ����
		if (!Animinstance || !attackMontage)
		{
			UE_LOG(LogTemp, Warning, TEXT("nullptr"));
			return;
		}

		// ������
		bAttacking = true;

		const char* comboList[] = { "Combo01", "Combo02" ,"Combo03" };

		UE_LOG(LogTemp, Warning, TEXT("ComboCount : %d"), ComboCount);

		// ���� ���콺 ��ư�� �������
		// �ִϸ��̼��� ���������� �ʾ�����
		if (!(Animinstance->Montage_IsPlaying(attackMontage)))
		{
			Animinstance->Montage_Play(attackMontage);
		}

		// �ִϸ��̼��� �������� ��
		else if (Animinstance->Montage_IsPlaying(attackMontage))
		{
			// ���� �������� �ִϸ��̼��� ������ ���� �ִϸ��̼� ����
			Animinstance->Montage_SetNextSection(FName(comboList[ComboCount - 1]), FName(comboList[ComboCount]), attackMontage);
		}
	}
}

void AMyCharacter::AttackInputChecking()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackInputChecking()"));

	if (ComboCount >= 2)
	{
		ComboCount = 0;
	}

	if (bComboAttack == true)
	{
		ComboCount += 1;
		bComboAttack = false;
		Attack();
	}
}

void AMyCharacter::UnArmWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("UnArmWeapon()"));
	bAttacking = false;

	if (!Animinstance || !AnimUnArm)
	{
		UE_LOG(LogTemp, Warning, TEXT("nullptr"));
		return;
	}

	Animinstance->Montage_Play(AnimUnArm, 2.0f);
}

void AMyCharacter::ArmWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("ArmWeapon()"));

	if (!Animinstance || !AnimArm)
	{
		UE_LOG(LogTemp, Warning, TEXT("nullptr"));
		return;
	}

	Animinstance->Montage_Play(AnimArm, 2.0f);
}

void AMyCharacter::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackEnd()"));

	bAttacking = false;
	bOverlapWeapon = false;
}

void AMyCharacter::MyOnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���ݿ� ���� ���Ͱ� "tagEnemy"�� ������ �ְ�, �÷��̾ �������϶���
	if (OtherComp->ComponentHasTag((FName("tagEnemy"))) && bAttacking && !bOverlapWeapon)
	{
		UE_LOG(LogTemp, Log, TEXT("test overlap"));
		bOverlapWeapon = true;

		// OtherActor���� WeaponDamage��ŭ�� �������� ����
		UGameplayStatics::ApplyDamage(OtherActor, WeaponDamage, NULL, GetOwner(), NULL);

		// ����Ʈ �߻��� ��ġ			
		FVector HitLocation = OverlappedComponent->GetComponentLocation();

		// ����Ʈ(���̾ư���)
		if (NS_Hit)
		{
			// ����� ������ġ�� ����Ʈ �߻�
			UE_LOG(LogTemp, Log, TEXT("NS_Hit : %s"), *HitLocation.ToString());
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Hit, HitLocation);
		}

		// ����
		if (SB_Hit)
		{
			//UGameplayStatics::PlaySoundAtLocation(GetWorld(), "����" , HitLocation);
		}
	}
}

void AMyCharacter::MyOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	HP -= Damage;

	if (UI_HP)
	{
		UE_LOG(LogTemp, Log, TEXT("UI_HP NOT NULL"));

		// HP�� ����
		UI_HP->Update_UserHpBar();
	}

	else
	{
		UE_LOG(LogTemp, Log, TEXT("UI_HP NULL"));
	}

	UE_LOG(LogTemp, Log, TEXT("My HP : %f"), HP);

	// HP�� 0���ϰ� �Ǹ� (����)
	if (HP <= 0.0)
	{
		MyCharcterDeath();
	}

	return Damage;
}

//void AMyCharacter::StartJump()
//{
//	bPressedJump = true;
//}
//
//void AMyCharacter::StopJump()
//{
//	bPressedJump = false;
//}