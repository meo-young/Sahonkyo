#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UGroomComponent;
class UInputAction;
class UInputComponent;
class UCameraComponent;
class UInteractionComponent;
struct FInputActionValue;

UCLASS()
class SAHONKYO_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	
public:
	void SetInputEnabled(const bool InInputEnabled);
	void PlayMonologue(USoundCue* InSoundCue);

protected:
	void DoMove(const FInputActionValue& MovementInput);
	void DoLook(const FInputActionValue& LookInput);
	void DoInteract(const FInputActionValue& InteractInput);

protected:
	/* ================== Input Action ================== */
	UPROPERTY(EditDefaultsOnly, Category = "변수|입력")
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수|입력")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "변수|입력")
	TObjectPtr<UInputAction> LookAction;


	/* ================== 컴포넌트 ================== */
	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<UInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "변수|컴포넌트")
	TObjectPtr<UAudioComponent> AudioComponent;

public:
	/* ================== Getter ================== */
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
};
