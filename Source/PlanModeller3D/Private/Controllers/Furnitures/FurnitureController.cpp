// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Furnitures/FurnitureController.h"


void UFurnitureController::Init_Implementation(UPrimaryDataAsset* DataAsset)
{
	IInitializable::Init_Implementation(DataAsset);
	Data = Cast<UFurnitureControllerData>(DataAsset);
}
