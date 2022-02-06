// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Components/Button.h"
#include "WidgetGameUI.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "WidgetSelectMenu.h"

// 설명부 텍스트 출력 + 별이미지 출력
void UWidgetSelectMenu::SetText_Expanation()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (MyGameInstance != nullptr)
	{
		switch (MyGameInstance->curCharacterNum)
		{
			// Warrior
			case 0:
			{
				// 직업 텍스트 출력
				FString Fstr = FString::Printf(TEXT("전사"));
				txtExplanation->SetText(FText::FromString(Fstr));
				
				// 별 이미지 
				ImgStar_01->SetVisibility(ESlateVisibility::Visible);
				ImgStar_02->SetVisibility(ESlateVisibility::Visible);
				ImgStar_03->SetVisibility(ESlateVisibility::Visible);
				ImgStar_04->SetVisibility(ESlateVisibility::Visible);
				ImgStar_05->SetVisibility(ESlateVisibility::Visible);

				ImgStar_11->SetVisibility(ESlateVisibility::Visible);
				ImgStar_12->SetVisibility(ESlateVisibility::Visible);
				ImgStar_13->SetVisibility(ESlateVisibility::Visible);
				ImgStar_14->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_15->SetVisibility(ESlateVisibility::Hidden);

				ImgStar_21->SetVisibility(ESlateVisibility::Visible);
				ImgStar_22->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_23->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_24->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_25->SetVisibility(ESlateVisibility::Hidden);				

				break;
			}

			// Magician
			case 1:
			{
				// 직업 텍스트 출력
				FString Fstr = FString::Printf(TEXT("마법사"));
				txtExplanation->SetText(FText::FromString(Fstr));

				// 별 이미지 
				ImgStar_01->SetVisibility(ESlateVisibility::Visible);
				ImgStar_02->SetVisibility(ESlateVisibility::Visible);
				ImgStar_03->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_04->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_05->SetVisibility(ESlateVisibility::Hidden);

				ImgStar_11->SetVisibility(ESlateVisibility::Visible);
				ImgStar_12->SetVisibility(ESlateVisibility::Visible);
				ImgStar_13->SetVisibility(ESlateVisibility::Visible);
				ImgStar_14->SetVisibility(ESlateVisibility::Visible);
				ImgStar_15->SetVisibility(ESlateVisibility::Visible);

				ImgStar_21->SetVisibility(ESlateVisibility::Visible);
				ImgStar_22->SetVisibility(ESlateVisibility::Visible);
				ImgStar_23->SetVisibility(ESlateVisibility::Visible);
				ImgStar_24->SetVisibility(ESlateVisibility::Hidden);
				ImgStar_25->SetVisibility(ESlateVisibility::Hidden);

				break;
			}
		}
	}
}

void UWidgetSelectMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//StaticClass() 함수를 이용하면 런타임 중에 해당 클래스를 나타내는 UClass를 얻어낼 수 있다.
	CameraDirecter123 = Cast<ACameraDirector>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraDirector::StaticClass()));

	// 버튼클릭시 커스텀함수를 호출할수있게 바인딩해줌(델리게이트)
	BtnLeft->OnClicked.AddDynamic(this, &UWidgetSelectMenu::OnClickBtnLeft);
	BtnRight->OnClicked.AddDynamic(this, &UWidgetSelectMenu::OnClickBtnRight);
	BtnSelect->OnClicked.AddDynamic(this, &UWidgetSelectMenu::OnClickBtnSelect);

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	// 설명부 텍스트 출력 + 별이미지 출력
	SetText_Expanation();
}

void UWidgetSelectMenu::OnClickBtnLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("LEFT"));

	if (CameraDirecter123 != nullptr)
	{
		CameraDirecter123->testFunction2();
		SetText_Expanation();
	}
}

void UWidgetSelectMenu::OnClickBtnRight()
{
	UE_LOG(LogTemp, Warning, TEXT("RIGHT"));

	if (CameraDirecter123 != nullptr)
	{
		CameraDirecter123->testFunction();
		SetText_Expanation();
	}
}

void UWidgetSelectMenu::OnClickBtnSelect()
{
	UE_LOG(LogTemp, Warning, TEXT("SELECT"));

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	switch (MyGameInstance->curCharacterNum)
	{
		// Warrior
	case 0:
		MyGameInstance->curCharacterPath = TEXT("/Game/Blueprints/BP_Warrior");
		UE_LOG(LogTemp, Warning, TEXT("SELECT BP_Warrior"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyGameInstance->curCharacterPath);
		break;

		// Magician
	case 1:
		MyGameInstance->curCharacterPath = TEXT("/Game/Blueprints/BP_Magician");
		UE_LOG(LogTemp, Warning, TEXT("SELECT BP_Magician"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyGameInstance->curCharacterPath);
		break;
	}

	if (MyGameInstance)
	{
		// 게임플레이 레벨로 이동	
		UGameplayStatics::OpenLevel(GetWorld(), FName(MyGameInstance->levelnamePlayGame_0));
	}
}


