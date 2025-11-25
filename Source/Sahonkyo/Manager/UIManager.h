#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIManager.generated.h"

class UDialogueWidget;
class UMonologueWidget;
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
	/* ========== Widget Class 모음입니다. ========== */
	UPROPERTY()
	TSubclassOf<UCrosshairWidget> CrosshairWidgetClass;
	
	UPROPERTY()
	TSubclassOf<UMonologueWidget> MonologueWidgetClass;

private:
	/* ========== Widget Instance 모음입니다. ========== */
	UPROPERTY()
	TObjectPtr<UCrosshairWidget> CrosshairWidgetInstance;
	
	UPROPERTY()
	TObjectPtr<UMonologueWidget> MonologueWidgetInstance;

public:
	/* ================== Getter ================== */
	FORCEINLINE UCrosshairWidget* GetCrosshairWidget() const { return CrosshairWidgetInstance; }
	FORCEINLINE UMonologueWidget* GetMonologueWidget() const { return MonologueWidgetInstance; }

};
