// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "CF_GroupMemberAddedMessage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_GroupMemberAddedMessageBase : public FCF_Message
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	int32 ContextId = -1;


	FCF_GroupMemberAddedMessageBase()
	{
		ContextId = -1;
	}

	FCF_GroupMemberAddedMessageBase(int32 _ContextId)
	{
		ContextId = _ContextId;
	}
};





template<typename ComponentType>
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_GroupMemberAddedMessage : public FCF_GroupMemberAddedMessageBase
{


	FCF_GroupMemberAddedMessage()
	{
		ContextId = -1;
	}

	FCF_GroupMemberAddedMessage(int32 _ContextId)
	{
		ContextId = _ContextId;
	}
};
