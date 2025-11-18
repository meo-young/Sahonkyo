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

void UInteractionComponent::ExecuteInteractIfPossible()
{
	if (CurrentItem)
	{
		if (CurrentItem->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_Interact(CurrentItem);
		}
	}
}

void UInteractionComponent::TraceForInteractable()
{
	// (1) 소유한 액터의 카메라 컴포넌트를 가져옵니다.
	AActor* Owner = GetOwner(); if (!Owner) return;
	UCameraComponent* CameraComponent = Owner->FindComponentByClass<UCameraComponent>(); if (!CameraComponent) return;
	
	// (2) 시작 위치와 끝 위치를 계산하여 Line Trace를 수행합니다.
	const FVector StartLocation = CameraComponent->GetComponentLocation();
	const FVector EndLocation = StartLocation + (CameraComponent->GetForwardVector() * TraceDistance);
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_INTERACTABLE, Params);
	
	// (3) Line Trace의 Hit Actor를 가져옵니다.
	AActor* NewDetectedActor = Hit.GetActor();
	
	// (4) 새로 감지된 액터가 현재 아이템과 다르다면, 상호작용 아이콘을 비활성화 합니다.
	if (NewDetectedActor != CurrentItem)
	{
		if (CurrentItem)
		{
			if (CurrentItem->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				IInteractable::Execute_OnInteractableImpossible(CurrentItem);
			}
		}
		CurrentItem = NewDetectedActor;
	}

	// (5) 히트된 액터의 상호작용 아이콘을 활성화 합니다.
	if (CurrentItem)
	{
		if (CurrentItem->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			IInteractable::Execute_OnInteractablePossible(CurrentItem);
		}
	}

#if WITH_EDITOR
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f, 0, 0.3f);
#endif
	
}
