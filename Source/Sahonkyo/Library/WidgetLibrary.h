#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetLibrary.generated.h"

class UImage;

UCLASS()
class SAHONKYO_API UWidgetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** 이미지의 투명도를 설정하는 함수입니다. */
	UFUNCTION(BlueprintCallable)
	static void SetImageOpacity(UImage* ImageWidget, const float Opacity);
	
};
