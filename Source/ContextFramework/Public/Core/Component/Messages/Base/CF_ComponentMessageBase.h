// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "CF_ComponentMessageBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_ComponentMessageBase : public FCF_Message
{


	
	GENERATED_BODY()
	
	FCF_ComponentMessageBase()
	{
		ContextId = -1;
		ComponentType = nullptr;
	}

	FCF_ComponentMessageBase(int32 ContextId, const UScriptStruct* _ComponentType)
		: ContextId(ContextId),
		  ComponentType(_ComponentType)
	{
	}


	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	int32 ContextId;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	const UScriptStruct* ComponentType;


	
	
};
