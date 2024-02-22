#pragma once

#include "CoreMinimal.h"
#include "LinetraceRay.generated.h"

USTRUCT(BlueprintType)
struct FLinetraceRay
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector End;
	
};
