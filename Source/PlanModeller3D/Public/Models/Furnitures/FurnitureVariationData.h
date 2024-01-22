#pragma once

#include "CoreMinimal.h"
#include "FurnitureVariationData.generated.h"

USTRUCT(BlueprintType)
struct FFurnitureVariationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Size;
	
	
};
