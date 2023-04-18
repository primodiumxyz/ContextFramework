// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/GameState/CF_WrapperGameState.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"


int32 ACF_WrapperGameState::GetContextId() const
{
	return ContextId;
}


const FCF_ArchType& ACF_WrapperGameState::GetContextArchetype() const
{
	return ContextArchetype;
}

void ACF_WrapperGameState::BeginPlay()
{
	Super::BeginPlay();
	if(IsInitializeContextOnBeginPlay)
	{
		ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
		CachedCF_Context = UCF_Statics::GetContextForId(this,ContextId);
	}
	
}

void ACF_WrapperGameState::Destroyed()
{
	Super::Destroyed();
	if(ContextId != -1)
		UCF_Statics::ReturnContextId(this,ContextId);
}

void ACF_WrapperGameState::FireEventOverNetwork_NetMulticast_Implementation(FInstancedStruct Message)
{
	if(GetNetMode() == ENetMode::NM_Client)
		UCF_EventStatics::FireEvent_InstancedStruct(this,Message);
}

void ACF_WrapperGameState::FireDoubleMessageTypeEventOverNetwork_NetMulticast_Implementation(const UScriptStruct* SecondaryMessageScriptStruct,FInstancedStruct Message)
{
	if(GetNetMode() == ENetMode::NM_Client)
		UCF_EventStatics::FireDoubleMessageTypeEvent_InstancedStruct(this,SecondaryMessageScriptStruct,Message);
}

ACF_WrapperGameState::ACF_WrapperGameState()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
}
