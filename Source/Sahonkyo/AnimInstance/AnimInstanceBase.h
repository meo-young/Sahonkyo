#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

class ACharacterBase;
class UCharacterMovementComponent;

UCLASS()
class SAHONKYO_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	/** 캐릭터의 이동 방향에 대한 변수입니다. */
	UPROPERTY(BlueprintReadOnly, Category = "변수")
	FVector2D MoveDirection;

	/** 캐릭터의 이동 속도에 대한 변수입니다. */
	UPROPERTY(BlueprintReadOnly, Category = "변수")
	float MoveSpeed;

private:
	/** 이 애니메이션 인스턴스가 소유하고 있는 캐릭터입니다. */
	UPROPERTY()
	TObjectPtr<ACharacterBase> Player = nullptr;

	/** 캐릭터의 이동 컴포넌트입니다. */
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> MovementComponent = nullptr;
	
};
