#include "CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Sahonkyo.h"
#include "Camera/CameraComponent.h"
#include "Component/InteractionComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Define/Define.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
	// 대사를 출력할 오디오 컴포넌트를 설정합니다.
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	
	// 상호작용 컴포넌트를 설정합니다.
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	
	// 카메라 컴포넌트를 설정합니다.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh());
	CameraComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	CameraComponent->bUsePawnControlRotation = true;
	
	// 1인칭 메쉬를 설정합니다.
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	// 캐릭터 이동 관련 설정합니다.
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;

	// 캡슐 콜리전 설정을 수정합니다.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_ICON_TRACE, ECR_Block);
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::DoMove);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::DoLook);
		}

		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::DoInteract);
		}
	}
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::SetInputEnabled(const bool InInputEnabled)
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PC->InputComponent))
		{
			// 모든 입력을 한 번에 제어
			EIC->bBlockInput = !InInputEnabled;
		}
	}
}

void ACharacterBase::DoMove(const FInputActionValue& MovementInput)
{
	// 사용자가 입력한 방향키 값을 2D 벡터로 변환합니다.
	const FVector2D MovementVector = MovementInput.Get<FVector2D>();

	// 방향키 값에 맞게 캐릭터를 이동시킵니다.
	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

void ACharacterBase::DoLook(const FInputActionValue& LookInput)
{
	// 사용자가 입력한 마우스 이동 값을 2D 벡터로 변환합니다.
	const FVector2D LookVector = LookInput.Get<FVector2D>();

	// 마우스 이동 값에 맞게 캐릭터의 시점을 회전시킵니다.
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ACharacterBase::DoInteract(const FInputActionValue& InteractInput)
{
	if (InteractionComponent)
	{
		InteractionComponent->ExecuteInteractIfPossible();
	}
}
