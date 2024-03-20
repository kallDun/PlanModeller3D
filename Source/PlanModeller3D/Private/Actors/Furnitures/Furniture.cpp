// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Furnitures/Furniture.h"
#include "Actors/Foundation/FoundationActor.h"


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
	TArray<AActor*> OverlappingActors;
	for (const auto Mesh : Meshes)
	{
		Mesh->GetOverlappingActors(OverlappingActors);
		for (const AActor* Actor : OverlappingActors)
		{
			if (Actor->IsA<AFurniture>())
			{
				return false;
			}
			if (Actor->IsA<AFoundationActor>())
			{
				return false;
			}
		}
	}
	return true;
}

void AFurniture::GetFromPool_Implementation(UPoolService* Pool)
{
	IPoolObject::GetFromPool_Implementation(Pool);
}

void AFurniture::ReturnToPool_Implementation(UPoolService* Pool)
{
	IPoolObject::ReturnToPool_Implementation(Pool);
}
