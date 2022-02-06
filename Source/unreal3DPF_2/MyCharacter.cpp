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

	// tagPlayer 태그 추가
	Tags.Add("tagPlayer");

	// 체력
	HP = 0.9f;

	// 구르기 속도
	RollingValue = 2500.f;
	bRolling = false;

	// 걷기, 달리기 속력
	Speed = SPEED_WALK;

	// 카메라줌 거리, 속력
	ZoomValue = 333.0f;
	ZoomSpeed = 15.0f;

	// 무기 소켓 위치	
	FName weaponSocket(TEXT("WeaponSocket"));

	// 캐릭터가 카메라의 회전을 따라서 회전하지 않도록 한다.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터의 이동
	GetCharacterMovement()->bOrientRotationToMovement = true; // 자동적으로 캐릭터의 이동방향을 움직이는 방향으로 맞춰줌
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); //캐릭터의 무브먼트를 규정하는 코드로, 캐릭터를 이동시키기 전에 이동 방향과 현재 캐릭터의 방향이 다르면 캐릭터를 이동 방향으로 초당 640도의 회전 속도로 회전시킨다음 이동
	GetCharacterMovement()->bConstrainToPlane = true; // 이동이 평면으로 제한 // 평면(네비게이션 메시)
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 캐릭터의 위치가 평면을 벗어난 상태라면 가까운 평면으로 붙여서 시작
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	GetCharacterMovement()->JumpZVelocity = 600.f;

	// 스프링암
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = ZoomValue;
	CameraBoom->bUsePawnControlRotation = true;

	// 카메라
	MyCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCharacterCamera"));
	MyCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MyCameraComponent->bUsePawnControlRotation = false;

	// 무기
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), weaponSocket);

	// 무기 충돌체
	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(Weapon);
	WeaponCollision->SetGenerateOverlapEvents(true); // overlap 이벤트를 쓰기위해서 켜줌	

	// 상호작용 충돌체
	InteractCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(RootComponent);
	InteractCollision->SetGenerateOverlapEvents(true); // overlap 이벤트를 쓰기위해서 켜줌	
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

	// 애님 인스턴스를 가져옴
	Animinstance = GetMesh()->GetAnimInstance();

	// 다이나믹 델리게이트 바인딩 // 실행할 함수 지정
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

	// 상하좌우 이동 
	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	// 달리기
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	InputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::RunEnd);

	// 점프
	//InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	//InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	// 공격
	InputComponent->BindAction("Attack01", IE_Pressed, this, &AMyCharacter::LMBDown);
	InputComponent->BindAction("Attack01", IE_Released, this, &AMyCharacter::LMBUp);

	// 덤블링
	InputComponent->BindAction("Rolling", IE_Pressed, this, &AMyCharacter::Rolling);

	// 상호작용(NPC와)
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);

	// 카메라 상하회전
	InputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	// 카메라 줌기능
	InputComponent->BindAxis("Zoom", this, &AMyCharacter::Zoom);

}

// E버튼 누름
void AMyCharacter::Interact()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AActor::StaticClass());	// 상호작용 충돌체와 겹친 Actor 반환

	UE_LOG(LogTemp, Warning, TEXT("Interact()"));

	for (auto overlapedActor : Result)
	{
		// 그 액터가 인터페이스가 구현되어있는가?
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

		// 컨트롤러 기준 Z축 앞으로만 이동하게함
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

		// 컨트롤러 기준 Z축 옆으로만 이동하게함
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

	// 줌 제한
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

	// 공격중이 아닐때만 공격함수 호출
	else if (bAttacking == false && bArmWeapon == true && bArmAniEnd)
	{
		Attack();
	}

	// 공격중일때
	else if (bAttacking == true && bArmWeapon == true && bArmAniEnd)
	{
		bComboAttack = true;
	}
}

void AMyCharacter::MyCharcterDeath()
{
	// 죽는 모션 재생
	Animinstance->Montage_Play(deathMontage);	

	// 람다를 통한 Delay 구현
	FTimerHandle testTimerHandle;
	float Time = 2.0f; // Time초 뒤
	GetWorld()->GetTimerManager().SetTimer(testTimerHandle, [&]()
		{
			// 코드 구현
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

			if (MyGameInstance)
			{
				UE_LOG(LogTemp, Warning, TEXT("MyGameInstance != nullptr"));

				if (MyGameInstance->WidgetGameover != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("MyGameInstance->WidgetGameover != nullptr"));

					// 위젯을 만들고 화면에 보여줌			
					CreateWidget(GetWorld(), MyGameInstance->WidgetGameover)->AddToViewport();

					// 효과음 재생
					MyGameInstance->PlayBGM(MyGameInstance->GameOvercue);

					// UI 입력모드
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

					// 마우스 커서 보이게
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

					// 게임 일시정지
					UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(true);
				}
			}

			// TimerHandle 초기화
			//GetWorld()->GetTimerManager().ClearTimer(testTimerHandle);
		}, Time, false);	// 반복하려면 false를 true로 변경
}

void AMyCharacter::Attack()
{
	if (bArmWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack()"));
		bLMBDown = true;

		// (안전상) 애님인스턴스와 어택몽타주가 둘중 하나라도 nullptr이면 리턴
		if (!Animinstance || !attackMontage)
		{
			UE_LOG(LogTemp, Warning, TEXT("nullptr"));
			return;
		}

		// 공격중
		bAttacking = true;

		const char* comboList[] = { "Combo01", "Combo02" ,"Combo03" };

		UE_LOG(LogTemp, Warning, TEXT("ComboCount : %d"), ComboCount);

		// 왼쪽 마우스 버튼을 누른경우
		// 애니메이션을 실행중이지 않았을때
		if (!(Animinstance->Montage_IsPlaying(attackMontage)))
		{
			Animinstance->Montage_Play(attackMontage);
		}

		// 애니메이션이 실행중일 때
		else if (Animinstance->Montage_IsPlaying(attackMontage))
		{
			// 현재 실행중인 애니메이션이 끝나고 다음 애니메이션 진행
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
	// 공격에 맞은 액터가 "tagEnemy"를 가지고 있고, 플레이어가 공격중일때만
	if (OtherComp->ComponentHasTag((FName("tagEnemy"))) && bAttacking && !bOverlapWeapon)
	{
		UE_LOG(LogTemp, Log, TEXT("test overlap"));
		bOverlapWeapon = true;

		// OtherActor에게 WeaponDamage만큼의 데미지를 가함
		UGameplayStatics::ApplyDamage(OtherActor, WeaponDamage, NULL, GetOwner(), NULL);

		// 이펙트 발생할 위치			
		FVector HitLocation = OverlappedComponent->GetComponentLocation();

		// 이펙트(나이아가라)
		if (NS_Hit)
		{
			// 무기와 맞은위치에 이펙트 발생
			UE_LOG(LogTemp, Log, TEXT("NS_Hit : %s"), *HitLocation.ToString());
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Hit, HitLocation);
		}

		// 사운드
		if (SB_Hit)
		{
			//UGameplayStatics::PlaySoundAtLocation(GetWorld(), "사운드" , HitLocation);
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

		// HP바 갱신
		UI_HP->Update_UserHpBar();
	}

	else
	{
		UE_LOG(LogTemp, Log, TEXT("UI_HP NULL"));
	}

	UE_LOG(LogTemp, Log, TEXT("My HP : %f"), HP);

	// HP가 0이하가 되면 (죽음)
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