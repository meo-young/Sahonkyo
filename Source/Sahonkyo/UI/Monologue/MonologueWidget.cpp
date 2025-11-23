#include "UI/Monologue/MonologueWidget.h"
#include "Sahonkyo.h"
#include "Components/TextBlock.h"

FReply UMonologueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// F키를 입력할 경우 위젯을 비활성화합니다.
	if (InKeyEvent.GetKey() == EKeys::F)
	{
		if (CurrentMonologueIndex < CachedMonologueText.Num())
		{
			ShowMonologue();
		}
		else
		{
			HideWidget();
		}
		
		LOG(TEXT("F키 입력"));
		
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMonologueWidget::ShowWidget(const TArray<FString>& InMonologueText)
{
	CachedMonologueText = InMonologueText;
	CurrentMonologueIndex = 0;
	ShowMonologue();	
	
	Super::ShowWidget();
}

void UMonologueWidget::ShowMonologue()
{
	Monologue_Text->SetText(FText::FromString(CachedMonologueText[CurrentMonologueIndex]));
	++CurrentMonologueIndex;
}
