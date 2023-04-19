// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/PoolManager/Subsystems/S_CF_PoolManager.h"


ACF_WrapperActor* US_CF_PoolManager::GetNewInstanceOf(TSoftClassPtr<ACF_WrapperActor> ActorBound)
{
	const auto AssetName = ActorBound.GetAssetName();
	if(!ActivePools.Contains(AssetName))
	{
		const TSubclassOf<ACF_WrapperActor> WrapperActorClass =ActorBound.LoadSynchronous();
		if(WrapperActorClass == nullptr)
			return nullptr;
		ActivePools.Add(AssetName,FActorWrapperPool(AssetName,WrapperActorClass));
	}
	if(ActivePools[AssetName].PooledActorWrappers.Num() > 0)
		return ActivePools[AssetName].PooledActorWrappers.Pop();
	else
		return GetWorld()->SpawnActor<ACF_WrapperActor>(ActivePools[AssetName].PooledActorWrapperClass);
	
}

bool US_CF_PoolManager::ReturnWrapperActorInstance(TSoftClassPtr<ACF_WrapperActor> ActorBound,
	ACF_WrapperActor* WrapperActorInstance)
{
	const auto AssetName = ActorBound.GetAssetName();
	if(!ActivePools.Contains(AssetName))
		return false;


	if(!ActivePools[AssetName].PooledActorWrappers.Contains(WrapperActorInstance))
		return false;
	
	ActivePools[AssetName].PooledActorWrappers.Add(WrapperActorInstance);
	return true;
}
