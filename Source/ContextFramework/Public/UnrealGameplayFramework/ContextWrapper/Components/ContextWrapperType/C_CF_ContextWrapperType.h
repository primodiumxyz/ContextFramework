// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "ContextFramework/Public/UnrealGameplayFramework/ContextWrapper/BaseClasses/Actor/CF_WrapperActor.h"
#include "UObject/Object.h"
#include "C_CF_ContextWrapperType.generated.h"

/**
 * 
 */

USTRUCT()
struct  CONTEXTFRAMEWORK_API FC_CF_ContextWrapperType : public FCF_Component
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSoftClassPtr<ACF_WrapperActor> ContextWrapperType = nullptr;

	


	

	FC_CF_ContextWrapperType()
	{
		ContextWrapperType = nullptr;
	}


	FC_CF_ContextWrapperType(TSoftClassPtr<ACF_WrapperActor> _ContextWrapperType)
	{
		ContextWrapperType = _ContextWrapperType;
	}

	
};
