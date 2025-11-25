#include "UI/Monologue/DialogueWidget.h"
#include "Character/CharacterBase.h"
#include "Components/TextBlock.h"
#include "Item/MonologueItem.h"
#include "Kismet/GameplayStatics.h"

void UDialogueWidget::ShowWidget(const FString& InDialogue)
{
	// 타이머를 해제합니다.
	GetWorld()->GetTimerManager().ClearTimer(Monologue_TimerHandle);
	
	// 대사의 길이를 추출합니다.
	const float MonologueLength = InDialogue.Len();
	
	// 대사를 UI에 표시합니다.
	Dialogue_Text->SetText(FText::FromString(InDialogue));
	
	// 대사의 길이에 따라 UI 출력 시간을 조정합니다.
	GetWorld()->GetTimerManager().SetTimer(Monologue_TimerHandle, this, &ThisClass::HideWidget, MonologueLength/5, false);
}
