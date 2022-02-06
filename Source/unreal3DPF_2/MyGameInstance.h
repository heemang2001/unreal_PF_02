// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "structOption.h"
#include "WidgetGameUI.h"
#include "WidgetGameOver.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UAudioComponent* PlayBGM(USoundBase* soundcue);

	UFUNCTION(BlueprintCallable)
	void SetOption(FStruct_Option curOption);

	UFUNCTION(BlueprintCallable)
	void GetOption();

	UFUNCTION(BlueprintCallable)
	void SetbTotitle(bool bCheck);
	
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* BGMcue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* GameOvercue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBGM = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSound = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTotitle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int curCharacterNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString curCharacterPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName levelnameTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName levelnameSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName levelnamePlayGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName levelnamePlayGame_0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> WidgetGameover;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> WidgetGameClear;
};
