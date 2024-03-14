#pragma once

#include "CoreMinimal.h"
#include "AreaGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FAreaGenerationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> GeneratedAreas = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> CustomAreas = {};
};
