// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealGameplayFramework/ContextWrapper/Interface/CF_Wrapper.h"
#include "UObject/Object.h"
#include "CF_WrapperObject.generated.h"

/**
 * 
 */
UCLASS(NotEditInlineNew)
class CONTEXTFRAMEWORK_API UCF_WrapperObject : public UObject, public ICF_Wrapper
{

private:
	GENERATED_BODY()

public:
	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FCF_ArchType ContextArchetype;
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	int32 ContextId;

	
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	FCF_Context CachedCF_Context;

	
	

	UFUNCTION(BlueprintCallable)
	virtual int32 GetContextId() const override;


	UFUNCTION(BlueprintCallable)
	virtual const FCF_ArchType& GetContextArchetype() const override;


public:

	// Sets default values for this actor's properties
	UCF_WrapperObject();


	UFUNCTION(BlueprintCallable)
	virtual void Initialize();

	UFUNCTION()
	virtual void FinishDestroy() override;

	
	

};
