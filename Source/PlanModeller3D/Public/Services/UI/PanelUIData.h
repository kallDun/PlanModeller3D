#pragma once

#include "CoreMinimal.h"
#include "ActionOnGetSingletonPanel.h"
#include "UObject/Object.h"
#include "PanelUIData.generated.h"

class UManagerUI;

USTRUCT(BlueprintType)
struct FPanelUIData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseNameAsPoolID = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!UseNameAsPoolID", EditConditionHides=true))
	FName PoolID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPanelUI> PanelClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSingleton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIsSingleton", EditConditionHides=true))
	EActionOnGetSingletonPanel ActionOnGetSingletonPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!bIsSingleton", EditConditionHides=true, ClampMin=2))
	int MaxCount = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELevelTransitionPoolBehaviour LevelTransitionBehaviour;
};
