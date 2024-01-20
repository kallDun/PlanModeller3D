// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolData.h"
#include "UObject/Object.h"
#include "PoolService.generated.h"


UCLASS(BlueprintType)
class PLANMODELLER3D_API UPoolService : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UObject*> UsedPool = {};

	UPROPERTY()
	TArray<UObject*> FreePool = {};

	UPROPERTY()
	FPoolData Data;
	
public:
	UFUNCTION()
	void Init(const FPoolData& PoolData);

	UFUNCTION()
	void Dispose();

	UFUNCTION(BlueprintCallable)
	UObject* GetFromPool();

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(UObject* Object);

private:
	UFUNCTION()
	UObject* CreateObject();

	UFUNCTION()
	void IncreasePoolSize(EPoolRule Rule, int Constant);
	
	UFUNCTION()
	static void ShowObject(UObject* Object);

	UFUNCTION()
	static void HideObject(UObject* Object);

	UFUNCTION()
	static void DestroyObject(UObject* Object);
};
