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

public:
	/** 상호작용이 가능한 오브젝트가 있을 경우 상호작용을 실행하는 함수입니다. */
	void ExecuteInteractIfPossible();

private:
	/** 전방에 상호작용이 가능한 오브젝트가 있는지 LineTrace를 수행하는 함수입니다. */
	void TraceForInteractable();

protected:
	/** Line Trace를 실시하는 거리입니다. */
	UPROPERTY(EditDefaultsOnly, Category = "변수|수치")
	float TraceDistance = 100.0f;

private:
	FHitResult Hit;
	FCollisionQueryParams Params;

	UPROPERTY()
	AActor* CurrentItem = nullptr;
		
};
