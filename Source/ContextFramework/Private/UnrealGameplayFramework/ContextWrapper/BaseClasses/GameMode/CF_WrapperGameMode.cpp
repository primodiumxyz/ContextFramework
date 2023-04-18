// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/GameMode/CF_WrapperGameMode.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"


int32 ACF_WrapperGameMode::GetContextId() const 
{
	return ContextId;
}


const FCF_ArchType& ACF_WrapperGameMode::GetContextArchetype() const 
{
	return ContextArchetype;
}

void ACF_WrapperGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(IsInitializeContextOnBeginPlay)
	{
		ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
		CachedCF_Context = UCF_Statics::GetContextForId(this,ContextId);
	}
	
}

void ACF_WrapperGameMode::Destroyed()
{
	Super::Destroyed();
	if(ContextId != -1)
		UCF_Statics::ReturnContextId(this,ContextId);
}

ACF_WrapperGameMode::ACF_WrapperGameMode()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
}
