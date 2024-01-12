#pragma once

#include "DMCompositeModels.h"
#include "DMParametricItem.generated.h"

USTRUCT(BlueprintType)
struct FDMParametricItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString Id;
	
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Position;

	UPROPERTY(BlueprintReadWrite)
	bool Enable;

	UPROPERTY(BlueprintReadWrite)
	bool Visible;

	UPROPERTY(BlueprintReadWrite)
	FDMCompositeModels CompositeModels;
};
