// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PoolObject.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPoolObject : public UInterface
{
	GENERATED_BODY()
};

class IPoolObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetFromPool(UPoolService* Pool);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReturnToPool(UPoolService* Pool);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPoolDispose(UPoolService* Pool);
};
