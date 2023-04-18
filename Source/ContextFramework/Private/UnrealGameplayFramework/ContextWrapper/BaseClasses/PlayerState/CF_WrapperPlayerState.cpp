// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/PlayerState/CF_WrapperPlayerState.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"


// Sets default values
ACF_WrapperPlayerState::ACF_WrapperPlayerState()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
}

void ACF_WrapperPlayerState::FireDoubleMessageTypeEventOverNetwork_ToOwningClient_Implementation(
	FInstancedStruct Message, const UScriptStruct* SecondaryScriptStruct)
{
	if(HasAuthority() && GetNetMode() == ENetMode::NM_Client)
		UCF_EventStatics::FireDoubleMessageTypeEvent_InstancedStruct(this,SecondaryScriptStruct,Message);
}

void ACF_WrapperPlayerState::FireDoubleMessageTypeEventOverNetwork_ToServer_Implementation(FInstancedStruct Message,
                                                                                           const UScriptStruct* SecondaryScriptStruct)
{
	if(HasAuthority() && GetNetMode() == ENetMode::NM_DedicatedServer)
		UCF_EventStatics::FireDoubleMessageTypeEvent_InstancedStruct(this,SecondaryScriptStruct,Message);
}

void ACF_WrapperPlayerState::FireEventOverNetwork_ToOwningClient_Implementation(FInstancedStruct Message)
{
	if(HasAuthority() && GetNetMode() == ENetMode::NM_Client)
		UCF_EventStatics::FireEvent_InstancedStruct(this,Message);
}

void ACF_WrapperPlayerState::FireEventOverNetwork_ToServer_Implementation(FInstancedStruct Message)
{
	if(GetNetMode() == ENetMode::NM_DedicatedServer)
		UCF_EventStatics::FireEvent_InstancedStruct(this,Message);
}


int32 ACF_WrapperPlayerState::GetContextId() const
{
	return ContextId;
}


const FCF_ArchType& ACF_WrapperPlayerState::GetContextArchetype() const
{
	return ContextArchetype;
}

void ACF_WrapperPlayerState::BeginPlay()
{
	if(IsInitializeContextOnBeginPlay)
	{
		ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
		CachedCF_Context = UCF_Statics::GetContextForId(this,ContextId);
	}
	
}

void ACF_WrapperPlayerState::Destroyed()
{
	if(ContextId != -1)
		UCF_Statics::ReturnContextId(this,ContextId);
}
