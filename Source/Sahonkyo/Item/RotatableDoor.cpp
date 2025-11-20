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
	// Actor Sequence 카메라의 월드 위치/회전을 구합니다.
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	ACharacterBase* PlayerPawn = Cast<ACharacterBase>(PC->GetPawn());

	const FVector DoorCamLocation = SequenceCameraComponent->GetComponentLocation();
	const FRotator DoorCamRotation = SequenceCameraComponent->GetComponentRotation();
	const FVector TargetLocation = DoorCamLocation - FVector(0.f, 0.f, 90.f);

	// 플레이어를 해당 위치로 순간이동합니다.
	PlayerPawn->SetActorLocationAndRotation(TargetLocation, DoorCamRotation);
	PC->SetControlRotation(DoorCamRotation);

	// 일정 시간 후에 플레이어 카메라로 전환합니다.
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARotatableDoor::InitViewTarget, 0.25f, false);
}

void ARotatableDoor::Interact_Implementation()
{
	Super::Interact_Implementation();

	PlayActorSequence();

	if (bIsInteractionOnce) DeactivateItemCollision();
	
	// 플레이어 카메라를 SequenceCameraComponent로 전환합니다.
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetViewTargetWithBlend(
			this,                   
			0.5f,                   
			VTBlend_Cubic
		);
	}
}

void ARotatableDoor::InitViewTarget()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	ACharacterBase* PlayerPawn = Cast<ACharacterBase>(PC->GetPawn());

	PC->SetViewTarget(PlayerPawn->GetCameraComponent()->GetOwner());

}
