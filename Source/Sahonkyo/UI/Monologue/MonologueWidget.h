#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "MonologueWidget.generated.h"

class AMonologueItem;
class UTextBlock;

UCLASS()
class SAHONKYO_API UMonologueWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	void ShowWidget(const TArray<FString>& InMonologueText, AMonologueItem* InItem);
	
	void ShowMonologue();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Monologue_Text;
	
private:
	TWeakObjectPtr<AMonologueItem> CurrentItem;
	TArray<FString> CachedMonologueText;
	uint8 CurrentMonologueIndex = 0;
	
};
