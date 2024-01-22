// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Initializable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ServicesAbstractFactory.generated.h"


UCLASS()
class PLANMODELLER3D_API UServicesAbstractFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template<class T>
	static T* CreateService(UObject* WorldContextObject, UPrimaryDataAsset* Data)
	{
		T* Service = NewObject<T>(WorldContextObject);
		if (T::StaticClass()->ImplementsInterface(UInitializable::StaticClass()))
		{
			auto Initializable = Cast<IInitializable>(Service);
			Initializable->Execute_Init(Service, Data);
		}
		return Service;
	}
	
};
