#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class SAHONKYO_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Interact();

	UFUNCTION(BlueprintNativeEvent)
	void OnInteractablePossible();

	UFUNCTION(BlueprintNativeEvent)
	void OnInteractableImpossible();

};
