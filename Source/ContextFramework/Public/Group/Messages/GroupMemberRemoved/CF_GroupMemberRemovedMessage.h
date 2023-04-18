// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "CF_GroupMemberRemovedMessage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_GroupMemberRemovedMessageBase : public FCF_Message
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	int32 ContextId = -1;


	FCF_GroupMemberRemovedMessageBase()
	{
		ContextId = -1;
	}

	FCF_GroupMemberRemovedMessageBase(int32 _ContextId)
	{
		ContextId = _ContextId;
	}
};

template<typename ComponentType>
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_GroupMemberRemovedMessage : public FCF_GroupMemberRemovedMessageBase
{
	

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	int32 ContextId = -1;


	FCF_GroupMemberRemovedMessage()
	{
		ContextId = -1;
	}

	FCF_GroupMemberRemovedMessage(int32 _ContextId)
	{
		ContextId = _ContextId;
	}
};
