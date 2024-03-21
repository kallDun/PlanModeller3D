#pragma once

#include "CoreMinimal.h"
#include "InstrumentInputType.h"
#include "InstrumentInputHint.generated.h"

USTRUCT(BlueprintType)
struct FInstrumentInputHint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInstrumentInputType InputType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ButtonAction = "Press";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Hint = "to use the instrument";
};
