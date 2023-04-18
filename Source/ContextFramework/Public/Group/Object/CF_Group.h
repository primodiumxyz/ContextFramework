// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "CF_Group.generated.h"



USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_Group 
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TArray<int32> Contexts;

	
	FCF_Group(TArray<int32> _Contexts)
	{
		Contexts = TArray<int32>(_Contexts);
	}
	
	FCF_Group()
	{
		Contexts = TArray<int32>();
	}
	
};




