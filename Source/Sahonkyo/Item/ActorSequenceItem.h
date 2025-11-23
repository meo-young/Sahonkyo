#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "ActorSequenceItem.generated.h"

class UCameraComponent;
class UActorSequence;
class UActorSequenceComponent;

UCLASS()
class SAHONKYO_API AActorSequenceItem : public AItemBase
{
	GENERATED_BODY()

public:
	AActorSequenceItem();
	
public:
	virtual void Interact_Implementation() override;
	virtual void OnInteractionEnd() override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayActorSequence();


private:
	void InitViewTarget();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<UCameraComponent> SequenceCameraComponent;

};
