#pragma once

#include "DMCompositeModels.h"
#include "DMParametricItem.generated.h"

USTRUCT()
struct FDMParametricItem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid Id;
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	bool Enable;

	UPROPERTY()
	bool Visible;

	UPROPERTY()
	FDMCompositeModels CompositeModels;
};
