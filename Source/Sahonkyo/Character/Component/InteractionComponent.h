#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAHONKYO_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/** 전방에 상호작용이 가능한 오브젝트가 있는지 LineTrace를 수행하는 함수입니다. */
	void TraceForInteractable();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수|수치")
	float TraceDistance = 200.0f;

private:
	FHitResult Hit;
	FCollisionQueryParams Params;
		
};
