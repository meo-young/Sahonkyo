#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "MonologueWidget.generated.h"

struct FMonologue;
class AMonologueItem;
class UTextBlock;

UCLASS()
class SAHONKYO_API UMonologueWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	void ShowWidget(const TArray<FMonologue>& InMonologue, AMonologueItem* InItem);
	
	void ShowMonologue();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Monologue_Text;
	
private:
	TArray<FMonologue> CachedMonologue;
	TWeakObjectPtr<AMonologueItem> CurrentItem;
	uint8 CurrentMonologueIndex = 0;
	
};
