#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

class UImage;

UCLASS()
class SAHONKYO_API UCrosshairWidget : public UWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Crosshair_Image;
	
};
