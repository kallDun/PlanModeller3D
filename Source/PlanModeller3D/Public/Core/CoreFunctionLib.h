// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreFunctionLib.generated.h"

class APlanModellerState;
class AMenuGameMode;
class APlanModellerGameMode;
class UPlanModellerGameInstance;

UCLASS()
class PLANMODELLER3D_API UCoreFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UPlanModellerGameInstance* GetPMInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static APlanModellerGameMode* GetPMGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static AMenuGameMode* GetMenuGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static APlanModellerState* GetPMState(const UObject* WorldContextObject);
	
};
