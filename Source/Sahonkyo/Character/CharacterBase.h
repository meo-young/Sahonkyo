#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UGroomComponent;
class UInputAction;
class UInputComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class SAHONKYO_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

protected:
	void DoMove(const FInputActionValue& MovementInput);
	void DoLook(const FInputActionValue& LookInput);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수|입력")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "변수|입력")
	TObjectPtr<UInputAction> LookAction;

};
