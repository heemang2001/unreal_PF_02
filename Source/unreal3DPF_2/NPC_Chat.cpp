// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Chat.h"

// Sets default values
ANPC_Chat::ANPC_Chat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ANPC_Chat::BeginPlay()
{
	Super::BeginPlay();	
	
}

// Called every frame
void ANPC_Chat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

