

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UObject/Object.h"
#include "CF_ArchType.generated.h"

/**
 * 
 */


struct FCF_Context;
 


USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_ArchType 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,EditAnywhere, meta = (BaseStruct = "CF_Component" ))
	TArray<FInstancedStruct> InitialComponents = TArray<FInstancedStruct>();


	FCF_ArchType()
	{
		InitialComponents = TArray<FInstancedStruct>();
	}

	FCF_ArchType(const TArray<FInstancedStruct> _InitialComponents)
	{
		InitialComponents = TArray<FInstancedStruct>();
		InitialComponents.SetNum(_InitialComponents.Num());
		for (int i = 0; i < _InitialComponents.Num(); ++i)
		{
			InitialComponents[i].InitializeAs(_InitialComponents[i].GetScriptStruct(),_InitialComponents[i].GetMemory());
		}
	}


	FCF_ArchType(const FCF_Context& Context);
	

	template<typename ComponentType>
	inline static ComponentType GetComponent(const FCF_ArchType& Context)
	{
		const auto ComponentId =ComponentType::StaticStruct()->GetName();
		for (auto InitialComponent : Context.InitialComponents)
		{
			if(ComponentId.Equals(InitialComponent.GetScriptStruct()->GetName()))
				return InitialComponent.Get<ComponentType>();
		}
		throw;
	}

	
};
