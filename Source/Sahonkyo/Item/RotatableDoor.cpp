#include "Item/RotatableDoor.h"
#include "Sahonkyo.h"

ARotatableDoor::ARotatableDoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARotatableDoor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	StartRotation = GetActorRotation();
}

void ARotatableDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsRotating) return;
	
	// 0 ~ 1 선형 증가 (RotationSpeed는 1초당 몇 배 속도로 진행할지)
	CurrentLerpAlpha += DeltaSeconds * RotationSpeed;
	const float Alpha = FMath::Clamp(CurrentLerpAlpha, 0.0f, 1.0f);

	// 시작 회전(StartRotation)에서 TargetRotation까지 선형 보간
	const FRotator CurrentRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
	SetActorRotation(CurrentRotation);

	// 회전이 거의 끝났다면 마무리
	if (Alpha >= 1.0f - KINDA_SMALL_NUMBER)
	{
		LOG(TEXT("회전 완료"));

		StartRotation = TargetRotation;
		CurrentLerpAlpha = 0.0f;
		SetActorRotation(TargetRotation); // 딱 맞게 정리
		bIsRotating = false;
		SetActorTickEnabled(false);
	}
}

void ARotatableDoor::Interact_Implementation()
{
	Super::Interact_Implementation();
	
	// 회전 중이라면 무시합니다.
	if (bIsRotating) return;

	// 열림/닫힘 상태에 따라 목표 회전값을 설정하고 회전을 시작합니다.
	TargetRotation = StartRotation + FRotator(0.0f, bIsOpened ? -RotationAngle : RotationAngle, 0.0f);
	bIsOpened = !bIsOpened;
	bIsRotating = true;
	SetActorTickEnabled(true);
}
