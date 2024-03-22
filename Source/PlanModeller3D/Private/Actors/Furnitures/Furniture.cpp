// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Furnitures/Furniture.h"
#include "Actors/Foundation/FoundationActor.h"


void AFurniture::Init(const FFurnitureData& FurnitureData, const FMFurniture& Model, const FString& Identifier)
{
	Data = FurnitureData;
	ID = Identifier;
	UpdateView(Model);
}

void AFurniture::AddMeshData(const int VariationIndex, UStaticMeshComponent* Mesh)
{
	const TArray<UMaterialInterface*> Materials = Mesh->GetMaterials();
	Meshes.Add(FFurnitureMeshData(VariationIndex, Mesh, Materials));
}

void AFurniture::UpdateView_Implementation(const FMFurniture& Model)
{
	SaveModel = Model;
	SetActorLocation(SaveModel.Location);
	SetActorRotation(SaveModel.Rotation);
	UpdateMeshesByVariation(SaveModel.VariationIndex, Data.Variations[SaveModel.VariationIndex]);
}

void AFurniture::UpdateMeshesByVariation_Implementation(const int VariationIndex, FFurnitureVariationData VariationData)
{
	for (const FFurnitureMeshData MeshData : Meshes)
	{
		if (MeshData.VariationIndex == VariationIndex)
		{
			MeshData.Mesh->SetVisibility(true);
			MeshData.Mesh->SetCollisionProfileName(SaveModel.IsPreview ? "FurniturePreviewPreset" : "FurniturePreset");
			MeshData.Mesh->SetSimulatePhysics(!SaveModel.IsPreview && Data.bIsPhysicsEnabled);
			for (int i = 0; i < MeshData.MeshMaterials.Num(); ++i)
			{
				MeshData.Mesh->SetMaterial(i, SaveModel.IsPreview ? PreviewMaterial : MeshData.MeshMaterials[i]);
			}
		}
		else
		{
			MeshData.Mesh->SetVisibility(false);
			MeshData.Mesh->SetCollisionProfileName("NoCollision");
			MeshData.Mesh->SetSimulatePhysics(false);
			for (int i = 0; i < MeshData.MeshMaterials.Num(); ++i)
			{
				MeshData.Mesh->SetMaterial(i, MeshData.MeshMaterials[i]);
			}
		}
	}
}

bool AFurniture::CheckPlacement_Implementation()
{
	TArray<AActor*> OverlappingActors;
	for (const FFurnitureMeshData MeshData : Meshes)
	{
		if (MeshData.VariationIndex != SaveModel.VariationIndex) continue;
		
		MeshData.Mesh->GetOverlappingActors(OverlappingActors);
		for (const AActor* Actor : OverlappingActors)
		{
			if (Actor->IsA<AFurniture>())
			{
				UpdateMaterials(false);
				return false;
			}
			if (Actor->IsA<AFoundationActor>())
			{
				UpdateMaterials(false);
				return false;
			}
		}
	}
	UpdateMaterials(true);
	return true;
}

void AFurniture::UpdateMaterials(const bool IsPlacementCorrect)
{
	for (const FFurnitureMeshData MeshData : Meshes)
	{
		if (MeshData.VariationIndex == SaveModel.VariationIndex)
		{
			for (int i = 0; i < MeshData.MeshMaterials.Num(); ++i)
			{
				auto Material = MeshData.Mesh->GetMaterial(i);
				MeshData.Mesh->SetMaterial(i, IsPlacementCorrect ? Material : WrongPlacementMaterial);
			}
		}
	}
}

void AFurniture::GetFromPool_Implementation(UPoolService* Pool)
{
	IPoolObject::GetFromPool_Implementation(Pool);
}

void AFurniture::ReturnToPool_Implementation(UPoolService* Pool)
{
	IPoolObject::ReturnToPool_Implementation(Pool);
}
