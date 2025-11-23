#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "MonologueWidget.generated.h"

class UTextBlock;

UCLASS()
class SAHONKYO_API UMonologueWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	void ShowWidget(const TArray<FString>& InMonologueText);
	
	void ShowMonologue();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Monologue_Text;
	
private:
	TArray<FString> CachedMonologueText;
	uint8 CurrentMonologueIndex = 0;
	
};
