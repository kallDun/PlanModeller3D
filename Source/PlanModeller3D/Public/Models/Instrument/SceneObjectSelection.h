#pragma once
#include "InstrumentAvailableSelection.h"
#include "SceneObjectSelection.generated.h"


USTRUCT(BlueprintType)
struct FSceneObjectSelection
{
	GENERATED_BODY()

	FSceneObjectSelection() {}

	FSceneObjectSelection(const EInstrumentAvailableSelection SelectionType, const FString& SelectionId, const FString& SelectionName) :
		SelectionType(SelectionType), SelectionId(SelectionId), SelectionName(SelectionName) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInstrumentAvailableSelection SelectionType = EInstrumentAvailableSelection::IAS_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SelectionId = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SelectionName = "None";

	bool operator==(const FSceneObjectSelection& Other) const
	{
		return SelectionType == Other.SelectionType && SelectionId == Other.SelectionId;
	}
};
