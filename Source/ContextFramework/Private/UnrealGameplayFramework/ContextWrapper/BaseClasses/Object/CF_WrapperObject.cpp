// Fill out your copyright notice in the Description page of Project Settings.



#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/Object/CF_WrapperObject.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"


int32 UCF_WrapperObject::GetContextId() const
{
	return ContextId;
}


const FCF_ArchType& UCF_WrapperObject::GetContextArchetype() const
{
	return ContextArchetype;
}



UCF_WrapperObject::UCF_WrapperObject()
{
	ContextId = -1;
	ContextArchetype = FCF_ArchType();
}

void UCF_WrapperObject::Initialize()
{
	ContextId = UCF_Statics::CreateNewContextFromArchType(this,ContextArchetype).ContextId;
	CachedCF_Context = UCF_Statics::GetContextForId(this,ContextId);
}

void UCF_WrapperObject::FinishDestroy()
{
	UObject::FinishDestroy();
	if(ContextId != -1)
		UCF_Statics::ReturnContextId(this,ContextId);
}
