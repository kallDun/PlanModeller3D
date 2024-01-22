// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Initialization/Initializable.h"
#include "UObject/Object.h"
#include "PoolsSystem.generated.h"

struct FPoolData;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPoolsSystem : public UObject, public IInitializable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<FName, class UPoolService*> Pools = {};

public:
	virtual void Init_Implementation(UPrimaryDataAsset* PoolSystemData) override;

	UFUNCTION(BlueprintCallable)
	UPoolService* CreatePool(FPoolData PoolData);

	UFUNCTION(BlueprintCallable)
	UPoolService* GetPool(FName PoolName) const;

	UFUNCTION(BlueprintCallable)
	void DestroyPool(FName PoolName);
};
