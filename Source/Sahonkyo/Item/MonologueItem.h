#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "MonologueItem.generated.h"

USTRUCT()
struct FMonologue
{
	GENERATED_USTRUCT_BODY()
public:
	/** 화면에 보일 독백 대사입니다. */
	UPROPERTY(EditAnywhere)
	FString MonologueText;
	
	/** 독백과 함께 출력될 음성입니다. */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> SoundCue;
};

UCLASS()
class SAHONKYO_API AMonologueItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact_Implementation() override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "변수|독백")
	TArray<FMonologue> Monologue;
	
};
