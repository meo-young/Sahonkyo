#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIManager.generated.h"

class UCrosshairWidget;

UCLASS()
class SAHONKYO_API UUIManager : public UObject
{
	GENERATED_BODY()

public:
	UUIManager();

public:
	/** UIManager의 초기화 함수입니다. */
	void InitUI(UWorld* World);

protected:
	// Widget Class 모음입니다.
	UPROPERTY()
	TSubclassOf<UCrosshairWidget> CrosshairWidgetClass;

private:
	// Widget Instance 모음입니다.
	UPROPERTY()
	TObjectPtr<UCrosshairWidget> CrosshairWidgetInstance;

public:
	FORCEINLINE UCrosshairWidget* GetCrosshairWidget() const { return CrosshairWidgetInstance; }
	
};
