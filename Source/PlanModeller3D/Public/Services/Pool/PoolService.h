// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolData.h"
#include "Services/Level/LevelType.h"
#include "UObject/Object.h"
#include "PoolService.generated.h"


class ULevelTransitionController;

UCLASS(BlueprintType)
class PLANMODELLER3D_API UPoolService : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ULevelTransitionController* TransitionController;
	
	UPROPERTY()
	TArray<UObject*> UsedPool = {};

	UPROPERTY()
	TArray<UObject*> FreePool = {};

	UPROPERTY()
	FPoolData Data;

	UPROPERTY()
	bool bIsInitialized = false;
	
public:
	UFUNCTION()
	void Init(const FPoolData& PoolData);

	UFUNCTION()
	void Dispose();

	UFUNCTION(BlueprintCallable)
	UObject* GetFromPool(UObject* Parent);

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(UObject* Object);

	UFUNCTION(BlueprintCallable)
	int GetUsedCount() const;

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetUsedPool() const;
	
private:
	UFUNCTION()
	void InitDefaultPoolObjects();
	
	UFUNCTION()
	UObject* CreateObject();

	UFUNCTION()
	void IncreasePoolSize(EPoolRule Rule, int Constant);
	
	UFUNCTION()
	void ShowObject(UObject* Object, UObject* Parent, bool BroadcastMessage = true);

	UFUNCTION()
	void HideObject(UObject* Object, bool BroadcastMessage = true);

	UFUNCTION()
	void DestroyObject(UObject* Object);

private:
	UFUNCTION()
	void OnLevelUnloaded(ELevelType Level);

	UFUNCTION()
	void OnLevelLoaded(ELevelType Level);
};
