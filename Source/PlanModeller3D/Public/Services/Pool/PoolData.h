#pragma once

#include "CoreMinimal.h"
#include "PoolRule.h"
#include "UObject/Object.h"
#include "PoolData.generated.h"

USTRUCT(BlueprintType)
struct FPoolData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PoolID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "1"))
	int InitialSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "1"))
	int MaxSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPoolRule GetFromPoolRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "0",
		EditCondition = "GetFromPoolRule == EAdditionPoolRule::AddConstant || GetFromPoolRule == EAdditionPoolRule::MultiplyByConstant", EditConditionHides=true))
	int GetFromPoolRuleConstant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPoolRule CloseToMaxSizeRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "0",
		EditCondition = "CloseToMaxSizeRule == EAdditionPoolRule::AddConstant || CloseToMaxSizeRule == EAdditionPoolRule::MultiplyByConstant", EditConditionHides=true))
	int CloseToMaxSizeRuleConstant;
	
};
