// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DeserializationFuncLib.generated.h"


UCLASS()
class PLANMODELLER3D_API UDeserializationFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool DeserializeJsonFile(const FString& FilePath, TSharedPtr<FJsonObject>& OutJsonObject);
};
