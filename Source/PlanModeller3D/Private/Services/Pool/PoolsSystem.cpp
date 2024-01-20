// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Pool/PoolsSystem.h"
#include "Services/Pool/PoolService.h"
#include "Services/Pool/PoolSystemData.h"

void UPoolsSystem::Init(UPoolSystemData* PoolSystemData)
{
	for (const auto Data : PoolSystemData->Pools)
	{
		CreatePool(Data);
	}
}

UPoolService* UPoolsSystem::CreatePool(const FPoolData PoolData)
{
	const auto Pool = NewObject<UPoolService>(this);
	Pool->Init(PoolData);
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
		Pools.Remove(PoolName);
	}
}
