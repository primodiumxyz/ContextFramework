// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/Messages/Base/CF_ComponentMessageBase.h"
#include "UObject/Object.h"
#include "CF_ComponentSetMessage.generated.h"



USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_ComponentSetMessageBase : public FCF_ComponentMessageBase
{
	GENERATED_BODY()
	FCF_ComponentSetMessageBase()
	{
		ComponentType = nullptr;
		ContextId = -1;
	}

	FCF_ComponentSetMessageBase(const int32 _ContextId, const UScriptStruct* _ComponentType)
	{
		ComponentType = _ComponentType;
		ContextId = _ContextId;
	}
};



template<typename ComponentType>
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_ComponentSetMessage : public FCF_ComponentSetMessageBase
{
	FCF_ComponentSetMessage()
	{
		ComponentType = nullptr;
		ContextId = -1;
	}

	FCF_ComponentSetMessage(const int32 _ContextId, const UScriptStruct* _ComponentType)
	{
		ComponentType = _ComponentType;
		ContextId = _ContextId;
	}
};
