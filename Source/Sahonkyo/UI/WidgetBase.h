#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

UCLASS()
class SAHONKYO_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void ShowWidget();

	UFUNCTION(BlueprintCallable)
	virtual void HideWidget();
	
};
