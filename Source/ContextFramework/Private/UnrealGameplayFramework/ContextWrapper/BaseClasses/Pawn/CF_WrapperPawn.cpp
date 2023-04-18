// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/Pawn/CF_WrapperPawn.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"

// Sets default values
ACF_WrapperPawn::ACF_WrapperPawn()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
}



int32 ACF_WrapperPawn::GetContextId() const
{
	return ContextId;
}


const FCF_ArchType& ACF_WrapperPawn::GetContextArchetype() const
{
	return ContextArchetype;
}

void ACF_WrapperPawn::SetContextId(int32 _ContextId)
{
	ContextId = _ContextId;
}



void ACF_WrapperPawn::BeginPlay()
{
	if(IsInitializeContextOnBeginPlay)
	{
		ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
		CachedCF_Context = UCF_Statics::GetContextForId(this,ContextId);
	}
	
}

void ACF_WrapperPawn::Destroyed()
{
	if(ContextId != -1)
		UCF_Statics::ReturnContextId(this,ContextId);
}
