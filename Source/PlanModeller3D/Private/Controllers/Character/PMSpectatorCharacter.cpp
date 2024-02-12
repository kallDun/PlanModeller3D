// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/PMSpectatorCharacter.h"
#include "Widgets/Properties/BoolPropertyConstructObject.h"
#include "Widgets/Properties/NumberPropertyConstructObject.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void APMSpectatorCharacter::SelectAsCurrent_Implementation()
{
	Super::SelectAsCurrent_Implementation();
}

void APMSpectatorCharacter::OnDeselect_Implementation()
{
	Super::OnDeselect_Implementation();
}

UPropertiesConstructData* APMSpectatorCharacter::GetProperties_Implementation()
{
	UPropertiesConstructData* Data = Super::GetProperties_Implementation();
	
	FOnGetNumberValue GetCameraFOV = FOnGetNumberValue();
	GetCameraFOV.BindDynamic(this, &APMSpectatorCharacter::GetCameraFOV);
	FOnSetNumberValue SetCameraFOV = FOnSetNumberValue();
	SetCameraFOV.BindDynamic(this, &APMSpectatorCharacter::SetCameraFOV);
	Data->NumberProperties.Add(FNumberPropertyConstructObject(
		0, FText::FromString("Camera FOV"), false, ENumberType::NT_Float, GetCameraFOV, SetCameraFOV, 0.0f, 180.0f));

	FOnGetNumberValue GetCameraSpeed = FOnGetNumberValue();
	GetCameraSpeed.BindDynamic(this, &APMSpectatorCharacter::GetCameraSpeed);
	FOnSetNumberValue SetCameraSpeed = FOnSetNumberValue();
	SetCameraSpeed.BindDynamic(this, &APMSpectatorCharacter::SetCameraSpeed);
	Data->NumberProperties.Add(FNumberPropertyConstructObject(
		1, FText::FromString("Camera Speed"), false, ENumberType::NT_Float, GetCameraSpeed, SetCameraSpeed, 0.0f, 100.0f));

	FOnGetBoolValue GetIsColliding = FOnGetBoolValue();
	GetIsColliding.BindDynamic(this, &APMSpectatorCharacter::GetIsColliding);
	FOnSetBoolValue SetIsColliding = FOnSetBoolValue();
	SetIsColliding.BindDynamic(this, &APMSpectatorCharacter::SetIsColliding);
	Data->BoolProperties.Add(FBoolPropertyConstructObject(
		0, FText::FromString("Is Colliding"), false, GetIsColliding, SetIsColliding));
	
	return Data;
}
