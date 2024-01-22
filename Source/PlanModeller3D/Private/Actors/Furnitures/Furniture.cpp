// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Furnitures/Furniture.h"


void AFurniture::Init(const FFurnitureData& FurnitureData)
{
	Data = FurnitureData;
}

void AFurniture::GetFromPool_Implementation(UPoolService* Pool)
{
	IPoolObject::GetFromPool_Implementation(Pool);
	
}

void AFurniture::ReturnToPool_Implementation(UPoolService* Pool)
{
	IPoolObject::ReturnToPool_Implementation(Pool);
	
}
