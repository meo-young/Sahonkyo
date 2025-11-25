#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

class UDialogueWidget;

UCLASS()
class SAHONKYO_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABaseGameMode();
	virtual void PostInitializeComponents() override;
	
public:
	UPROPERTY()
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UDialogueWidget> DialogueWidgetInstance;
	
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UDialogueWidget* GetDialogueWidget() const { return DialogueWidgetInstance; }
	
};
