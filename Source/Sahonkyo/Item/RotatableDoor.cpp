#include "Item/RotatableDoor.h"
#include "Sahonkyo.h"
#include "Camera/CameraComponent.h"
#include "Character/CharacterBase.h"
#include "Character/PlayerControllerBase.h"

ARotatableDoor::ARotatableDoor()
{
	SequenceCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SequenceCameraComponent"));
	SequenceCameraComponent->SetupAttachment(RootComponent);
}

void ARotatableDoor::OnInteractionEnd()
{
	Super::OnInteractionEnd();
	
	if (!PlayerController.Get() || !Player.Get())
	{
		LOG(TEXT("PlayerController 혹은 Player가 유효하지 않습니다"));
	}
	
	// Actor Sequence 카메라의 월드 위치/회전을 구합니다.
	const FVector DoorCamLocation = SequenceCameraComponent->GetComponentLocation();
	const FRotator DoorCamRotation = SequenceCameraComponent->GetComponentRotation();
	const FVector TargetLocation = DoorCamLocation - FVector(0.f, 0.f, 90.f);

	// 플레이어를 해당 위치로 순간이동합니다.
	Player->SetActorLocationAndRotation(TargetLocation, DoorCamRotation);
	PlayerController->SetControlRotation(DoorCamRotation);

	// 일정 시간 후에 플레이어 카메라로 전환합니다.
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARotatableDoor::InitViewTarget, 0.25f, false);
}

void ARotatableDoor::Interact_Implementation()
{
	Super::Interact_Implementation();

	// 액터 시퀀스를 재생합니다.
	PlayActorSequence();
	
	// 플레이어 카메라를 SequenceCameraComponent로 전환합니다.
	if (PlayerController.Get())
	{
		PlayerController->SetViewTargetWithBlend(
			this,                   
			0.5f,                   
			VTBlend_Cubic
		);
	}
}

void ARotatableDoor::InitViewTarget()
{
	if (!PlayerController.Get() || !Player.Get())
	{
		LOG(TEXT("PlayerController 혹은 Player가 유효하지 않습니다"));
	}
	
	PlayerController->SetViewTarget(Player->GetCameraComponent()->GetOwner());
}
