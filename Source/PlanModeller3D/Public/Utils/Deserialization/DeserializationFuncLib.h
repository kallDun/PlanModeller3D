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
	template <typename TStruct>
	static bool DeserializeJsonFileByPath(const FString& FilePath, TStruct& OutStruct);
};
