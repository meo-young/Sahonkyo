#include "Animation/Notify/AnimNotify_Footstep.h"

#include "Sahonkyo.h"
#include "Define/Define.h"
#include "Enum/ESFX.h"
#include "Library/SoundLibrary.h"

void UAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// Notify를 호출한 메시의 소유자를 가져온다.
	const AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner)) return;

	const UWorld* World = Owner->GetWorld();
	if (!IsValid(World)) return;
	
	// PhysicalMaterial을 가져오기 위한 쿼리 파라미터를 설정한다.
	QueryParams.bReturnPhysicalMaterial = true;
	
	// 액터의 -150.0f 아래 위치를 계산한다.
	const FVector CurrentLocation = Owner->GetActorLocation();
	const FVector DownVector = Owner->GetActorUpVector() * -200.0f;
	const FVector TargetLocation = CurrentLocation + DownVector;

	// LineTrace 실시한다.
	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		CurrentLocation,
		TargetLocation,
		ECC_FOOTSTEP,
		QueryParams
		);

#if WITH_EDITOR
	DrawDebugLine(World, CurrentLocation, TargetLocation, FColor::Green, false, 1.0f, 0, 2.0f);
#endif
	
	// Surface Type에 따른 발걸음 소리를 재생한다.
	if (bHit)
	{
		if (HitResult.PhysMaterial.IsValid())
		{
			LOG(TEXT("%s Surface Type: %d"), *Owner->GetName(), HitResult.PhysMaterial->SurfaceType.GetIntValue());
			switch (HitResult.PhysMaterial->SurfaceType)
			{
			case SURFACE_WOOD:
				USoundLibrary::PlaySFXInLocation(Owner, ESFX::Footstep_Wood, HitResult.ImpactPoint);
				break;

			case SURFACE_CONCRETE:
				USoundLibrary::PlaySFXInLocation(Owner, ESFX::Footstep_Concrete, HitResult.ImpactPoint);
				break;

			case SURFACE_CARPET:
				USoundLibrary::PlaySFXInLocation(Owner, ESFX::Footstep_Carpet, HitResult.ImpactPoint);
				break;
				
			case SURFACE_TILE:
				USoundLibrary::PlaySFXInLocation(Owner, ESFX::Footstep_Tile, HitResult.ImpactPoint);
				break;
			
			default:
				USoundLibrary::PlaySFXInLocation(Owner, ESFX::Footstep_Wood, HitResult.ImpactPoint);
				break;
			}
		}
	}
}
