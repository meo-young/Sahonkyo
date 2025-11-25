#include "Core/BaseGameMode.h"
#include "Sahonkyo.h"
#include "UI/Monologue/DialogueWidget.h"

ABaseGameMode::ABaseGameMode()
{
	static ConstructorHelpers::FClassFinder<UDialogueWidget> WBP_DialogueWidgetClass(TEXT("/Game/_Sahonkyo/HUD/WBP_Dialogue"));
	if (WBP_DialogueWidgetClass.Succeeded())
	{
		LOG(TEXT("Dialogue Widget Class 로드 성공"));
		DialogueWidgetClass = WBP_DialogueWidgetClass.Class;
	}
}

void ABaseGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (DialogueWidgetClass)
	{
		DialogueWidgetInstance = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
	}
}
