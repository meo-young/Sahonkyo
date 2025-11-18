#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

class UImage;

UCLASS()
class SAHONKYO_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 위젯을 화면에 표시하는 함수입니다. */
	UFUNCTION(BlueprintCallable)
	virtual void ShowWidget();

	/** 위젯을 화면에서 숨기는 함수입니다. */
	UFUNCTION(BlueprintCallable)
	virtual void HideWidget();

	/** 이미지의 투명도를 설정하는 함수입니다. */
	UFUNCTION(BlueprintCallable)
	virtual void SetImageOpacity(UImage* Image, const float Opacity, const float Duration = 0.0f);

private:
	

private:
	FTimerHandle OpacityTimerHandle;
	
};
