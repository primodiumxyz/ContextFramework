// Fill out your copyright notice in the Description page of Project Settings.


#include "ContextFramework/Public/UnrealGameplayFramework/ContextWrapper/BaseClasses/PlayerController/CF_WrapperPlayerController.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"


ACF_WrapperPlayerController::ACF_WrapperPlayerController()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
}



int32 ACF_WrapperPlayerController::GetContextId() const
{
	return ContextId;
}


const FCF_ArchType& ACF_WrapperPlayerController::GetContextArchetype() const
{
	return ContextArchetype;
}

void ACF_WrapperPlayerController::BeginPlay()
{
	if(IsInitializeContextOnBeginPlay)
	{
		ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
		CachedCF_Context = UCF_Statics::GetContextForId(this,ContextId);
	}
	
}

void ACF_WrapperPlayerController::Destroyed()
{
	if(ContextId != -1)
		UCF_Statics::ReturnContextId(this,ContextId);
}
