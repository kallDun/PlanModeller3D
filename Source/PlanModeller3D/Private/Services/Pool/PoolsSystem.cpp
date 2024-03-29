// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Pool/PoolsSystem.h"
#include "Services/Pool/PoolService.h"
#include "Services/Pool/PoolSystemData.h"


void UPoolsSystem::Init_Implementation(UPrimaryDataAsset* PoolSystemData)
{
	IInitializable::Init_Implementation(PoolSystemData);
	const auto Data = Cast<UPoolSystemData>(PoolSystemData);
	for (const auto PoolData : Data->Pools)
	{
		CreatePool(PoolData);
	}	
}

UPoolService* UPoolsSystem::CreatePool(const FPoolData PoolData)
{
	UPoolService* Pool = NewObject<UPoolService>(this);
	Pool->Init(PoolData);
	Pool->OnDispose.AddDynamic(this, &UPoolsSystem::UnregisterPool);
	Pools.Add(PoolData.PoolID, Pool);
	return Pool;
}

UPoolService* UPoolsSystem::GetPool(const FName PoolName) const
{
	return Pools.FindRef(PoolName);
}

void UPoolsSystem::DestroyPool(const FName PoolName)
{
	if (Pools.Contains(PoolName))
	{
		Pools[PoolName]->Dispose();
	}
}

void UPoolsSystem::UnregisterPool(UPoolService* Service)
{
	Pools.Remove(Service->Data.PoolID);
}
