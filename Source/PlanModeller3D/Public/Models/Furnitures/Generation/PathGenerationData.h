#pragma once

#include "CoreMinimal.h"
#include "PathGenerationData.generated.h"

USTRUCT(BlueprintType)
struct FPathGenerationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> GeneratedPathes = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> CustomPathes = {};
};
