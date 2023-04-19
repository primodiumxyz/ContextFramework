// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/Actor/CF_WrapperActor.h"
#include "UObject/Object.h"
#include "ActorWrapperPool.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FActorWrapperPool 
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FString PoolId = "";

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<ACF_WrapperActor> PooledActorWrapperClass = nullptr;


	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<ACF_WrapperActor*> PooledActorWrappers= TArray<ACF_WrapperActor*>();

	FActorWrapperPool()
	{
		PoolId = "";
		PooledActorWrapperClass = nullptr;
		PooledActorWrappers= TArray<ACF_WrapperActor*>();
	}

	FActorWrapperPool(FString _PoolId, TSubclassOf<ACF_WrapperActor> _PooledActorWrapperClass)
	{
		PoolId = _PoolId;
		PooledActorWrapperClass = _PooledActorWrapperClass;
		PooledActorWrappers= TArray<ACF_WrapperActor*>();
	}

	

	

	
};
