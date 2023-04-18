// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Core/ArchType/CF_ArchType.h"
#include "CF_Context.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_Context 
{
	GENERATED_BODY()

	FCF_Context() = default;

	FCF_Context(bool _IsValid)
	{
		IsValid = false;
		ContextId = -1;
	}
	
	FCF_Context(int32 _ContextId,const FCF_ArchType& FromContext)
	{
		ContextId = _ContextId;
		Components = TMap<FString, FInstancedStruct>();
		for (auto FromComponent : FromContext.InitialComponents)
		{
			FInstancedStruct Component;
			Component.InitializeAs(FromComponent.GetScriptStruct(),FromComponent.GetMemory());
			Components.Add(FromComponent.GetScriptStruct()->GetName(),Component);
		}
		IsValid = true;
	}

	FCF_Context(int32 _ContextId,const FCF_Context& FromContext)
	{
		ContextId = _ContextId;
		Components = TMap<FString, FInstancedStruct>();
		for (auto FromComponent : FromContext.Components)
		{
			FInstancedStruct Component;
			Component.InitializeAs(FromComponent.Value.GetScriptStruct(),FromComponent.Value.GetMemory());
			Components.Add(FromComponent.Value.GetScriptStruct()->GetName(),Component);
		}
		IsValid = true;
	}

	FCF_Context(int32 _ContextId)
		: ContextId(_ContextId)
	{
		Components = TMap<FString, FInstancedStruct>();
		IsValid = true;
	}

	FCF_Context(int32 _ContextId, const TMap<FString, FInstancedStruct>& _Components)
		: ContextId(_ContextId)
	{
		Components = TMap<FString,FInstancedStruct>();
		for (const auto Component :_Components)
		{
			FInstancedStruct InstancedStruct;
			InstancedStruct.InitializeAs(Component.Value.GetScriptStruct(),Component.Value.GetMemory());
			Components.Add(Component.Value.GetScriptStruct()->GetName(),InstancedStruct);
		}
		IsValid = true;
		
	}


	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	int32 ContextId = -1;

	UPROPERTY(BlueprintReadOnly,EditAnywhere, meta = (BaseStruct = "CF_Component" ))
	TMap<FString, FInstancedStruct> Components = TMap<FString, FInstancedStruct>();

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool IsValid = true;


	template<typename ComponentType>
	inline static const ComponentType& GetComponent(const FCF_Context& Context)
	{
		const auto ComponentId =ComponentType::StaticStruct()->GetName();
		return Context.Components[ComponentId].template Get<ComponentType>();
	}
	

	static void SetComponent(FCF_Context& Context,FInstancedStruct Component)
	{
		const auto ComponentId =Component.GetScriptStruct()->GetName(); 
		Context.Components[ComponentId] = Component;
	}

	

	static void AddComponent(FCF_Context& Context,FInstancedStruct Component)
	{
		Context.Components.Add(Component.GetScriptStruct()->GetName(),Component);
	}

	static void RemoveComponent(FCF_Context& Context,FInstancedStruct Component)
	{
		Context.Components.Remove(Component.GetScriptStruct()->GetName());
	}

	static void RemoveComponent(FCF_Context& Context,FString ComponentName)
	{
		Context.Components.Remove(ComponentName);
	}
	
};
