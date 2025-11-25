#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "DialogueWidget.generated.h"

struct FMonologue;
class UTextBlock;

UCLASS()
class SAHONKYO_API UDialogueWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	void ShowWidget(const FString& InDialogue);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Dialogue_Text;
	
private:
	FTimerHandle Monologue_TimerHandle;
	
};
