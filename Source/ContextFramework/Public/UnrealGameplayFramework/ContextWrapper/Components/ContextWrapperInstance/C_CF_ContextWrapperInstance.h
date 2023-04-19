// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/Actor/CF_WrapperActor.h"
#include "C_CF_ContextWrapperInstance.generated.h"




USTRUCT()
struct  CONTEXTFRAMEWORK_API FC_CF_ContextWrapperInstance : public FCF_Component
{
	GENERATED_BODY()


	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	ACF_WrapperActor* ContextWrapperInstance = nullptr;


	

	FC_CF_ContextWrapperInstance()
	{
		ContextWrapperInstance = nullptr;

	}


	FC_CF_ContextWrapperInstance(ACF_WrapperActor* _ContextWrapperInstance)
	{
		ContextWrapperInstance = _ContextWrapperInstance;
	}

	
};
