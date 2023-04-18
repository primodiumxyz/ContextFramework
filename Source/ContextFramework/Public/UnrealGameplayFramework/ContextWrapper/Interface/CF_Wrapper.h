// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Context/CF_Context.h"
#include "UObject/Interface.h"
#include "CF_Wrapper.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UCF_Wrapper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CONTEXTFRAMEWORK_API ICF_Wrapper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	virtual int32 GetContextId() const
	{
		return -1;
	}
	
	
	virtual const FCF_ArchType& GetContextArchetype() const 
	{
		throw;
	}


	virtual void SetContextId(int32 _ContextId)
	{
		
	}
	


	
};
