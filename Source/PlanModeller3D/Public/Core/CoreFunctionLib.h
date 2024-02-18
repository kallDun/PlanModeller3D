// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreFunctionLib.generated.h"

class UInstrumentsManager;
class UCharactersManager;
class UFurnitureController;
class UFoundationController;
class ULevelTransitionController;
class UPoolsSystem;
class UManagerUI;
class USavingService;
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

	// SERVICES

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static USavingService* GetSavingService(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static ULevelTransitionController* GetTransitionController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UPoolsSystem* GetPoolsSystem(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UManagerUI* GetManagerUI(const UObject* WorldContextObject);

	// CONTROLLERS

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UFoundationController* GetFoundationController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UFurnitureController* GetFurnitureController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UCharactersManager* GetCharactersManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Core", meta=(HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UInstrumentsManager* GetInstrumentsManager(const UObject* WorldContextObject);
	
};
