// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_CF_SpawnContextWrapperInstanceFromType.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API US_CF_SpawnContextWrapperInstanceFromType : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	//temporary solution final should just not be able to spawn a wrapper that is not present
	//currently server also detects client assets
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION()
	void OnContextWrapperTypeComponentSet(const UObject* Invoker,FCF_ComponentSetMessageBase ContextWrapperTypeSet);


	
};
