#pragma once

#include "CoreMinimal.h"
#include "PlacedFurnitureGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FPlacedFurnitureGenerationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> GeneratedFurnitureNames = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> CustomFurnitureNames = {};
};
