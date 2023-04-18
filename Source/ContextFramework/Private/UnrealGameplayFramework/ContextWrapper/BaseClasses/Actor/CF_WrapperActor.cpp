// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/Actor/CF_WrapperActor.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"


int32 ACF_WrapperActor::GetContextId() const 
{
	return ContextId;
}


const FCF_ArchType& ACF_WrapperActor::GetContextArchetype() const 
{
	return ContextArchetype;
}

void ACF_WrapperActor::SetContextId(int32 _ContextId)
{
	ContextId  = _ContextId;
}

void ACF_WrapperActor::BeginPlay()
{
	Super::BeginPlay();
	if(IsInitializeContextOnBeginPlay)
	{
		ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
		CachedCF_Context = UCF_Statics::GetContext(this);
	}
	
}

void ACF_WrapperActor::Destroyed()
{
	if(ContextId != -1 && IsInitializeContextOnBeginPlay)
		UCF_Statics::ReturnContextId(this,ContextId);
	
	Super::Destroyed();
}

void ACF_WrapperActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ACF_WrapperActor::ACF_WrapperActor()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
	PrimaryActorTick.bCanEverTick = true;
}
