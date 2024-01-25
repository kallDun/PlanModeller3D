// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Models/Plan/DMPlan.h"
#include "Models/Plan3D/MPlan.h"
#include "Services/Save/AbstractSaveData.h"
#include "UObject/Object.h"
#include "PlanModellerSaveData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnModelChanged, ECrudActionType, ActionType, EPlanModelType, ModelType, FString, ObjectId);

UCLASS(Blueprintable, BlueprintType)
class PLANMODELLER3D_API UPlanModellerSaveData : public UAbstractSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnModelChanged OnModelChanged;
	
	UPROPERTY()
	FString FilePath;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDMPlan Plan2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMPlan* Plan3D;

	virtual void Init(const FString& Name) override
	{
		Super::Init(Name);

		if (FString FileData = ""; FFileHelper::LoadFileToString(FileData, *FilePath))
		{
			FJsonObjectConverter::JsonObjectStringToUStruct<FDMPlan>(FileData, &Plan2D, 0, 0);
		}
		Plan3D = NewObject<UMPlan>(this);
	}
};
