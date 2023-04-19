// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UnrealGameplayFramework/PoolManager/Pool/ActorWrapperPool.h"
#include "S_CF_PoolManager.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API US_CF_PoolManager : public UGameInstanceSubsystem
{

public:

	
	GENERATED_BODY()

	
	UPROPERTY()
	TMap<FString, FActorWrapperPool> ActivePools = TMap<FString, FActorWrapperPool>();
	
	

	UFUNCTION()
	ACF_WrapperActor* GetNewInstanceOf(TSoftClassPtr<ACF_WrapperActor> ActorBound);



	UFUNCTION()
	bool ReturnWrapperActorInstance(TSoftClassPtr<ACF_WrapperActor> ActorBound, ACF_WrapperActor* WrapperActorInstance);
	

	
};
