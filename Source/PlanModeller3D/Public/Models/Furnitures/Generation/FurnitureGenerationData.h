#pragma once

#include "CoreMinimal.h"
#include "SelectFurnitureGenerationData.h"
#include "FurnitureGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FFurnitureGenerationData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSelectFurnitureGenerationData SelectFurnitureComponentData;
	
};
