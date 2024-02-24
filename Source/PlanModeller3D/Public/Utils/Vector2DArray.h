#pragma once

#include "CoreMinimal.h"
#include "Vector2DArray.generated.h"

USTRUCT(BlueprintType)
struct FVector2DArray
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> Points = {};
	
};
