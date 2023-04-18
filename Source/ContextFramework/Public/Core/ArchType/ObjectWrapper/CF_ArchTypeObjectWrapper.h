// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ArchType/CF_ArchType.h"
#include "UObject/Object.h"
#include "CF_ArchTypeObjectWrapper.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class CONTEXTFRAMEWORK_API UCF_ArchTypeObjectWrapper : public UObject
{

public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FCF_ArchType ContextArchType = FCF_ArchType();
};
