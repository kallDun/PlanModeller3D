// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Deserialization/DeserializationFuncLib.h"
#include "JsonObjectConverter.h"


template <typename TStruct>
bool UDeserializationFuncLib::DeserializeJsonFileByPath(const FString& FilePath, TStruct* OutStruct)
{
	FString FileData = "";
	if (!FFileHelper::LoadFileToString(FileData, *FilePath)) return false;
	return FJsonObjectConverter::JsonObjectStringToUStruct(FileData, OutStruct, 0, 0);
}
