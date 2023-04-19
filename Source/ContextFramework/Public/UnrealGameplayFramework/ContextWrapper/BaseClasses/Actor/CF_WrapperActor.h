// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealGameplayFramework/ContextWrapper/Interface/CF_Wrapper.h"
#include "CF_WrapperActor.generated.h"

UCLASS(Blueprintable,BlueprintType)
class CONTEXTFRAMEWORK_API ACF_WrapperActor : public AActor, public ICF_Wrapper
{
public:

	// should only be used for in level actors
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool IsInitializeContextOnBeginPlay = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FCF_ArchType ContextArchetype;
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	int32 ContextId;
	

	
	

	UFUNCTION(BlueprintCallable)
	virtual int32 GetContextId()const override;


	UFUNCTION(BlueprintCallable)
	virtual const FCF_ArchType& GetContextArchetype()const  override;

	UFUNCTION(BlueprintCallable)
	virtual void SetContextId(int32 _ContextId) override;

	virtual void BeginPlay() override;

	virtual void Destroyed() override;


	virtual void Tick(float DeltaSeconds) override;
	
private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACF_WrapperActor();


};
