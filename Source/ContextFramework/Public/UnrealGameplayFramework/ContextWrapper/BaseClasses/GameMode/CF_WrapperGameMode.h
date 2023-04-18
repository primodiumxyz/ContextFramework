// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameMode.h"
#include "UnrealGameplayFramework/ContextWrapper/Interface/CF_Wrapper.h"
#include "CF_WrapperGameMode.generated.h"

UCLASS()
class CONTEXTFRAMEWORK_API ACF_WrapperGameMode : public AGameMode,public ICF_Wrapper
{
public:


	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool IsInitializeContextOnBeginPlay = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FCF_ArchType ContextArchetype;
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	int32 ContextId;

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	FCF_Context CachedCF_Context;

	
	

	UFUNCTION(BlueprintCallable)
	virtual int32 GetContextId() const override ;


	UFUNCTION(BlueprintCallable)
	virtual const FCF_ArchType& GetContextArchetype()const override;

	virtual void BeginPlay() override;

	virtual void Destroyed() override;


private:
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ACF_WrapperGameMode();


};
