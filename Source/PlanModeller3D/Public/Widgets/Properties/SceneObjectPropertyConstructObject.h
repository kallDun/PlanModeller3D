#pragma once
#include "Models/Instrument/SceneObjectSelection.h"
#include "SceneObjectPropertyConstructObject.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FSceneObjectSelection, FOnGetSceneObjectValue);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSetSceneObjectValue, const FSceneObjectSelection, Value);

USTRUCT(BlueprintType)
struct FSceneObjectPropertyConstructObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Order;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,	meta = (Bitmask, BitmaskEnum = "EInstrumentAvailableSelection"))
	uint8 AvailableSelections;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnGetSceneObjectValue GetValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FOnSetSceneObjectValue SetValue;
	
};
