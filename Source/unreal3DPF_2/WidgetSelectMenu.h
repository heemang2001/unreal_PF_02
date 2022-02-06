// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CameraDirector.h"
#include "WidgetSelectMenu.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL3DPF_2_API UWidgetSelectMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACameraDirector> FindClassType;

protected:
	virtual void NativeConstruct() override; // C++�� ���� ������

public:	
	UPROPERTY(meta = (BindWidget))
	class UButton* BtnLeft;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnRight;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnSelect;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* txtExplanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACameraDirector* CameraDirecter123;

public:
	UFUNCTION()
	void OnClickBtnLeft();

	UFUNCTION()
	void OnClickBtnRight();

	UFUNCTION()
	void OnClickBtnSelect();

	UFUNCTION()
	void SetText_Expanation();

// �� �̹���(ü��, ���ݷ�, ��Ÿ�)
public:
	// ü��
	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_01;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_02;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_03;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_04;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_05;

	// ���ݷ�
	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_11;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_12;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_13;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_14;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_15;

	// ��Ÿ�
	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_21;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_22;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_23;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_24;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImgStar_25;
	

};
