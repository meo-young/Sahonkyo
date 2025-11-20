#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UImage;

UCLASS()
class SAHONKYO_API UItemWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	void SetObjectImage(UTexture2D* InTexture);
	void SetObjectImageActive(const bool bIsActive);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Key_F_Image;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Object_Image;
	
};
