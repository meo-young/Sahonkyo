#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "MonologueItem.generated.h"

UCLASS()
class SAHONKYO_API AMonologueItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void Interact_Implementation() override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "변수|독백")
	TArray<FString> MonologueText;
	
};
