#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "RotatableDoor.generated.h"

UCLASS()
class SAHONKYO_API ARotatableDoor : public AItemBase
{
	GENERATED_BODY()

public:
	ARotatableDoor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	virtual void Interact_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, Category = "변수|수치")
	float RotationAngle = 90.f;

	UPROPERTY(EditAnywhere, Category = "변수|수치")
	uint8 bIsOpened : 1 = false;

	UPROPERTY(EditAnywhere, Category = "변수|수치")
	float RotationSpeed = 2.f;

private:
	uint8 bIsRotating : 1 = false;
	FRotator TargetRotation = FRotator::ZeroRotator;
	FRotator StartRotation;        
	float CurrentLerpAlpha = 0.0f; 
	
};
