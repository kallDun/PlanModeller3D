#pragma once

#include "CoreMinimal.h"
#include "InstrumentInputData.generated.h"

USTRUCT(BlueprintType)
struct FInstrumentInputData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ExitInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PreviewInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2f TwoAxisInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OneAxisInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerNextInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerPreviousInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerUndoInput;
	
};
