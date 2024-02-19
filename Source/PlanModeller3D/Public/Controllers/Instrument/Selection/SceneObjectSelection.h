#pragma once
#include "InstrumentAvailableSelection.h"
#include "SceneObjectSelection.generated.h"


USTRUCT(BlueprintType)
struct FSceneObjectSelection
{
	GENERATED_BODY()

	FSceneObjectSelection() {}

	FSceneObjectSelection(const EInstrumentAvailableSelection SelectionType, const FString& SelectionId) :
		SelectionType(SelectionType), SelectionId(SelectionId) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInstrumentAvailableSelection SelectionType = EInstrumentAvailableSelection::IAS_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SelectionId = "None";

	bool operator==(const FSceneObjectSelection& Other) const
	{
		return SelectionType == Other.SelectionType && SelectionId == Other.SelectionId;
	}
};
