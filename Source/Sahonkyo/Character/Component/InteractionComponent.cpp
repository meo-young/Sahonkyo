#include "Character/Component/InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Sahonkyo.h"
#include "Define/Define.h"
#include "Interface/Interactable.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	Params.AddIgnoredActor(GetOwner());
}

void UInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceForInteractable();
}

void UInteractionComponent::TraceForInteractable()
{
	// (1) 소유한 액터를 가져옵니다.
	AActor* Owner = GetOwner();
	if (!Owner) return;

	// (2) 카메라 컴포넌트를 찾습니다.
	UCameraComponent* CameraComponent = Owner->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent) return;
	
	// (3) 시작 위치와 끝 위치를 계산합니다.
	const FVector StartLocation = CameraComponent->GetComponentLocation();
	const FVector EndLocation = StartLocation + (CameraComponent->GetForwardVector() * TraceDistance);

	// (4) 라인 트레이스를 수행합니다.
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_INTERACTABLE, Params);

	// (5) 히트된 액터가 상호작용 인터페이스를 구현했는지 확인하고 상호작용을 수행합니다.
	if (AActor* HitActor = Hit.GetActor())
	{
		if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			LOG(TEXT("상호작용 가능 오브젝트를 찾았다"));
			IInteractable::Execute_Interact(HitActor);
		}
	}

#if WITH_EDITOR
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f, 0, 0.3f);
#endif
	
}
