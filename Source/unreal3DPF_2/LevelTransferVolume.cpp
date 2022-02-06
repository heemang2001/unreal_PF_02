#include "Engine/Classes/Components/BoxComponent.h" // �ڽ� ������Ʈ ���
#include "Kismet/GameplayStatics.h"	// ���� �̵��Լ�
#include "MyGameInstance.h"
#include "LevelTransferVolume.h"

// Sets default values
ALevelTransferVolume::ALevelTransferVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevelTransferVolume::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance)
	{
		TransferLevelName = MyGameInstance->levelnamePlayGame.ToString();
	}	
}

// Called every frame
void ALevelTransferVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransferVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);

	if (Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, (FName)TransferLevelName);
	}
}
