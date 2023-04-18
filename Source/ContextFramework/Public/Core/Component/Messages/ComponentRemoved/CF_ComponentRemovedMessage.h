// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/Messages/Base/CF_ComponentMessageBase.h"
#include "UObject/Object.h"
#include "CF_ComponentRemovedMessage.generated.h"

/**
 * 
*/



USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_ComponentRemovedMessageBase : public FCF_ComponentMessageBase
{
	GENERATED_BODY()
	FCF_ComponentRemovedMessageBase()
	{
		ComponentType = nullptr;
		ContextId = -1;
	}

	FCF_ComponentRemovedMessageBase(const int32 _ContextId, const UScriptStruct* _ComponentType)
	{
		ComponentType = _ComponentType;
		ContextId = _ContextId;
	}

	

	
};

template<typename ComponentType>
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_ComponentRemovedMessage : public FCF_ComponentRemovedMessageBase
{
	FCF_ComponentRemovedMessage()
	{
		ComponentType = nullptr;
		ContextId = -1;
	}

	FCF_ComponentRemovedMessage(const int32 _ContextId, const UScriptStruct* _ComponentType)
	{
		ComponentType = _ComponentType;
		ContextId = _ContextId;
	}

	

	
};
