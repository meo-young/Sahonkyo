#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UWidgetComponent;
class UItemWidget;
class USphereComponent;

UCLASS()
class SAHONKYO_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnIconTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnIconTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "변수|메시")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "변수|콜리전")
	TObjectPtr<USphereComponent> IconTriggerCollision;

	UPROPERTY(EditDefaultsOnly, Category = "변수|콜리전")
	TObjectPtr<USphereComponent> InteractCollision;

	UPROPERTY(EditDefaultsOnly, Category = "변수|아이콘")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, Category = "변수|UI")
	TObjectPtr<UWidgetComponent> ItemWidgetComponent;

};
