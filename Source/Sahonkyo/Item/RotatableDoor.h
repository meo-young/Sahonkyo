#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "RotatableDoor.generated.h"

class UCameraComponent;
class UActorSequence;
class UActorSequenceComponent;

UCLASS()
class SAHONKYO_API ARotatableDoor : public AItemBase
{
	GENERATED_BODY()

public:
	ARotatableDoor();
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayActorSequence();

	virtual void Interact_Implementation() override;

protected:
	virtual void OnInteractionEnd() override;

private:
	void InitViewTarget();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<UCameraComponent> SequenceCameraComponent;

private:
	uint8 bHasInteracted : 1 = false;

};
