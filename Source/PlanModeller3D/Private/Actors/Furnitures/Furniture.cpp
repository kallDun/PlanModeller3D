// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Furnitures/Furniture.h"


void AFurniture::Init(const FFurnitureData& FurnitureData, const FMFurniture& Model, const FString& Identifier)
{
	Data = FurnitureData;
	ID = Identifier;
	UpdateView(Model);
}

void AFurniture::UpdateView_Implementation(const FMFurniture& Model)
{
	SaveModel = Model;
}

bool AFurniture::CheckPlacement_Implementation()
{
	return true; // TODO: add collision check
}

void AFurniture::GetFromPool_Implementation(UPoolService* Pool)
{
	IPoolObject::GetFromPool_Implementation(Pool);
}

void AFurniture::ReturnToPool_Implementation(UPoolService* Pool)
{
	IPoolObject::ReturnToPool_Implementation(Pool);
}
