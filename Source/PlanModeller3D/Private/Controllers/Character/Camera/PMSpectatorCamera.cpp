// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Character/Camera/PMSpectatorCamera.h"
#include "Widgets/Properties/PropertiesConstructData.h"


void UPMSpectatorCamera::SelectCameraAsCurrent_Implementation()
{
	Super::SelectCameraAsCurrent_Implementation();
}

void UPMSpectatorCamera::OnDeselectCamera_Implementation()
{
	Super::OnDeselectCamera_Implementation();
}

UPropertiesConstructData* UPMSpectatorCamera::GetProperties_Implementation()
{
	UPropertiesConstructData* Data = Super::GetProperties_Implementation();
	
	FOnGetNumberValue GetCameraFOV = FOnGetNumberValue();
	GetCameraFOV.BindDynamic(this, &UPMSpectatorCamera::GetCameraFOV);
	FOnSetNumberValue SetCameraFOV = FOnSetNumberValue();
	SetCameraFOV.BindDynamic(this, &UPMSpectatorCamera::SetCameraFOV);
	Data->NumberProperties.Add(FNumberPropertyConstructObject(
		0, FText::FromString("Camera FOV"), false, ENumberType::NT_Float, GetCameraFOV, SetCameraFOV, 0.0f, 180.0f));

	FOnGetNumberValue GetCameraSpeed = FOnGetNumberValue();
	GetCameraSpeed.BindDynamic(this, &UPMSpectatorCamera::GetCameraSpeed);
	FOnSetNumberValue SetCameraSpeed = FOnSetNumberValue();
	SetCameraSpeed.BindDynamic(this, &UPMSpectatorCamera::SetCameraSpeed);
	Data->NumberProperties.Add(FNumberPropertyConstructObject(
		1, FText::FromString("Camera Speed"), false, ENumberType::NT_Float, GetCameraSpeed, SetCameraSpeed, 0.0f, 100.0f));

	FOnGetBoolValue GetIsColliding = FOnGetBoolValue();
	GetIsColliding.BindDynamic(this, &UPMSpectatorCamera::GetIsColliding);
	FOnSetBoolValue SetIsColliding = FOnSetBoolValue();
	SetIsColliding.BindDynamic(this, &UPMSpectatorCamera::SetIsColliding);
	Data->BoolProperties.Add(FBoolPropertyConstructObject(
		0, FText::FromString("Is Colliding"), false, GetIsColliding, SetIsColliding));
	
	return Data;
}
