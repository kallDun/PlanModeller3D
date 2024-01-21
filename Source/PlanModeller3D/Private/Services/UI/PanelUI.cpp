// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/UI/PanelUI.h"
#include "Services/Pool/PoolService.h"


void UPanelUI::Close()
{
	PoolService->ReturnToPool(this);
}

void UPanelUI::GetFromPool_Implementation(UPoolService* Pool)
{
	IPoolObject::GetFromPool_Implementation(Pool);
	PoolService = Pool;
}

void UPanelUI::ReturnToPool_Implementation(UPoolService* Pool)
{
	IPoolObject::ReturnToPool_Implementation(Pool);
	OnPanelClosed.Broadcast();
	OnPanelClosed.Clear();
}
