// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CF_DelegateHandle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_DelegateHandle 
{
	GENERATED_BODY()

	FCF_DelegateHandle()
	{
		DelegateHandle =FDelegateHandle();
		MessageScriptStruct = nullptr;
		HasSecondaryMessageScript = false;
		SecondaryMessageScriptStruct = nullptr;
	}

	FCF_DelegateHandle(const FDelegateHandle& _DelegateHandle, UScriptStruct* _MessageScriptStruct)
	{
		DelegateHandle = _DelegateHandle;
		MessageScriptStruct = _MessageScriptStruct;
		HasSecondaryMessageScript = false;
		SecondaryMessageScriptStruct = nullptr;
	}


	FCF_DelegateHandle(const FDelegateHandle& _DelegateHandle, UScriptStruct* _MessageScriptStruct, UScriptStruct* _SecondaryMessageScriptStruct)
	{
		DelegateHandle = _DelegateHandle;
		MessageScriptStruct = _MessageScriptStruct;
		SecondaryMessageScriptStruct = _SecondaryMessageScriptStruct;
		HasSecondaryMessageScript = true;
	}
	
	
	FDelegateHandle DelegateHandle;

	UPROPERTY(BlueprintReadOnly)
	UScriptStruct* MessageScriptStruct;

	UPROPERTY(BlueprintReadOnly)
	bool HasSecondaryMessageScript = false;

	UPROPERTY(BlueprintReadOnly)
	UScriptStruct* SecondaryMessageScriptStruct;
	
};
