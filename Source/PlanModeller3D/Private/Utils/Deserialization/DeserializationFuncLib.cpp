// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/Deserialization/DeserializationFuncLib.h"
#include "JsonObjectConverter.h"

bool UDeserializationFuncLib::DeserializeJsonFile(const FString& FilePath, TSharedPtr<FJsonObject>& OutJsonObject)
{
	FString FileContents;
	if (!FFileHelper::LoadFileToString(FileContents, *FilePath))
	{
		// Handle file reading error
		UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
		return false;
	}
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContents);
	return FJsonSerializer::Deserialize(Reader, OutJsonObject);
}
