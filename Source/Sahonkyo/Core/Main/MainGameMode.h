#pragma once

#include "CoreMinimal.h"
#include "Core/BaseGameMode.h"
#include "MainGameMode.generated.h"

class UUIManager;

UCLASS()
class SAHONKYO_API AMainGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UUIManager> UIManager;
	
};
