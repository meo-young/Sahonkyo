#include "UI/Monologue/MonologueWidget.h"
#include "Sahonkyo.h"
#include "Character/CharacterBase.h"
#include "Components/TextBlock.h"
#include "Core/Main/MainGameMode.h"
#include "Item/MonologueItem.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UMonologueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	LOG(TEXT("Monologue 시작"));

	SetIsFocusable(true);
	SetKeyboardFocus();
}

void UMonologueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// 매 프레임 포커스 확인 및 유지합니다.
	if (!HasKeyboardFocus())
	{
		SetKeyboardFocus();
	}
}

void UMonologueWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	CurrentMonologueIndex = 0;
}

FReply UMonologueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// F키를 입력할 경우 위젯을 비활성화합니다.
	if (InKeyEvent.GetKey() == EKeys::F)
	{
		if (CurrentMonologueIndex < CachedMonologue.Num())
		{
			ShowMonologue();
		}
		else
		{
			HideWidget();
			
			CurrentItem->OnInteractionEnd();
		}
		
		LOG(TEXT("F키 입력"));
		
		return FReply::Handled();
	}
	
	return FReply::Handled();
}

void UMonologueWidget::ShowWidget(const TArray<FMonologue>& InMonologue, AMonologueItem* InItem)
{
	CurrentItem = InItem;
	CachedMonologue = InMonologue;
	CurrentMonologueIndex = 0;
	ShowMonologue();	

	Super::ShowWidget();
}

void UMonologueWidget::ShowMonologue()
{
	ACharacterBase* Player = Cast<ACharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	Player->PlayMonologue(CachedMonologue[CurrentMonologueIndex].SoundCue);
	Monologue_Text->SetText(FText::FromString(CachedMonologue[CurrentMonologueIndex].MonologueText));
	++CurrentMonologueIndex;
}
