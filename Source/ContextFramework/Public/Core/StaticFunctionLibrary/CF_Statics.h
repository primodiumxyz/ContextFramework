// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Context/CF_Context.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "CF_Statics.generated.h"


class US_CF_Core;
UENUM()
enum class ECF_GetComponentResult : uint8
{
	Valid,
	NotValid,
};


/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API UCF_Statics :	public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	
	inline static FInstancedStruct InvalidComponent = FInstancedStruct();
	//
	inline static FCF_Context InvalidContext = FCF_Context(false);



#pragma region "Create Context"


	

	// UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	// static FCF_Context* CreateNewContextPointer(const UObject* WorldContextObject);

	
	
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static const FCF_Context& CreateNewContext(const UObject* WorldContextObject);

	
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static const FCF_Context& CreateNewContextFrom(const UObject* WorldContextObject, const FCF_Context From);

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static const FCF_Context& CreateNewContextFromArchType(const UObject* WorldContextObject, const FCF_ArchType From);


#pragma endregion 



	
#pragma region "Return Context"
	
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static void ReturnContextId(const UObject* WorldContextObject, int32 ContextId);

#pragma endregion 




#pragma region "Get Context"
	

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static const TArray<FCF_Context>& GetContexts(const UObject* WorldContextObject) ;

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static TArray<FCF_Context> GetContextsForIds(const UObject* WorldContextObject, const TArray<int32>& ContextIds ) ;


#pragma endregion 


#pragma region "Get Context"
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static const FCF_Context& GetContextForId(const UObject* WorldContextObject, int32 ContextId);


	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static const FCF_Context& GetContext(const UObject* WorldContextObject);



#pragma endregion 

#pragma region "Copy Context"
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static void CopyContextFromTo(const FCF_Context& From, FCF_Context& To)
	{
		To.Components.Empty();
		for (auto FromComponent : From.Components)
		{
			FInstancedStruct ToComponent;
			ToComponent.InitializeAs(FromComponent.Value.GetScriptStruct(),FromComponent.Value.GetMemory());
			To.Components.Add(FromComponent.Value.GetScriptStruct()->GetName(),ToComponent);
		}
	}

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static void CopyToContextFromArchType(const FCF_ArchType From, FCF_Context& To)
	{
		To.Components.Empty();
		for (auto FromComponent : From.InitialComponents)
		{
			FInstancedStruct ToComponent;
			ToComponent.InitializeAs(FromComponent.GetScriptStruct(),FromComponent.GetMemory());
			To.Components.Add(FromComponent.GetScriptStruct()->GetName(),ToComponent);
		}
	}


#pragma endregion "Copy Context"

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static void CopyComponentsFromArchtype(const UObject* WorldContextObject,const FCF_ArchType& FromArchType, int32 ToContextId)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				CF_CoreSubSystem->CopyComponentsFromArchtype(FromArchType,ToContextId);
			}
		}
	}

	


#pragma region Get Context Id
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static int32 GetContextId(const UObject* WorldContextObject);

#pragma endregion


	// UFUNCTION(BlueprintCallable, Category="ContextFramework",  meta=(WorldContext="WorldContextObject", DeterminesOutputType="ComponentClass", DynamicOutputParam="OutComponent"))
	// static void GetComponentOfType(const UObject* WorldContextObject, UScriptStruct* ComponentClass, UStruct* OutComponent);

	
	#pragma region "Has Component CPP"
	
	template<typename ComponentType>
	static bool HasComponent_Template(const UObject* WorldContextObject)
	{
		return HasComponent(WorldContextObject,ComponentType::StaticStruct());
	}

	template<typename ComponentType>
	static bool HasComponentForContextId_Template(const UObject* WorldContextObject, int32 ContextId)
	{
		return HasComponentForContextId(WorldContextObject,ContextId,ComponentType::StaticStruct());
	}
#pragma endregion 

	
#pragma region "Has Component BP"
	
	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static bool HasComponent(const UObject* WorldContextObject, UScriptStruct* ScriptStruct);

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static bool HasComponentForContextId(const UObject* WorldContextObject, int32 ContextId,UScriptStruct* ScriptStruct);
#pragma endregion 
#pragma region "Get Component CPP"


	
	
	template<typename ComponentType>
	inline static const ComponentType& GetComponentOfContextId(const UObject* WorldContextObject, int32 ContextId)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				return CF_CoreSubSystem->GetComponent_Template<ComponentType>(ContextId);
			}
		}
		throw;
	}

	template<typename ComponentType>
	inline static ComponentType& GetComponent(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				return CF_CoreSubSystem->GetComponent_Template<ComponentType>(GetContextId(WorldContextObject));
			}
		}
		throw;
	}
#pragma endregion 
	
#pragma region "Get Component Instanced Struct"

	UFUNCTION(BlueprintCallable, Category="ContextFramework")
	static const FInstancedStruct& GetComponentInstancedStructOfContextId(const UObject* WorldContextObject, int32 ContextId, const UScriptStruct* ScriptStruct);

	UFUNCTION(BlueprintCallable, Category="ContextFramework")
	static const FInstancedStruct& GetComponentInstancedStruct(const UObject* WorldContextObject, const UScriptStruct* ScriptStruct);

#pragma endregion 


#pragma region "Get Component BP"
	
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "ContextFramework", meta = (WorldContext="WorldContextObject",CustomStructureParam = "Value",ExpandEnumAsExecs = "ExecResult"))
	static void GetComponentOfContextId(ECF_GetComponentResult& ExecResult,const UObject* WorldContextObject,const int32 ContextId, int32& Value);
	
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "ContextFramework", meta = (WorldContext="WorldContextObject",CustomStructureParam = "Value",ExpandEnumAsExecs = "ExecResult"))
	static void GetComponent(ECF_GetComponentResult& ExecResult,const UObject* WorldContextObject, int32& Value);
	
#pragma endregion 



#pragma region "Set Component Instanced Struct"

	UFUNCTION(BlueprintCallable, Category="ContextFramework")
	static void SetComponentInstancedStructOfContextId(const UObject* WorldContextObject, int32 ContextId, FInstancedStruct Component);

	UFUNCTION(BlueprintCallable, Category="ContextFramework")
	static void SetComponentInstancedStruct(const UObject* WorldContextObject,  FInstancedStruct Component);

#pragma endregion 
#pragma region "Set Component BP"

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "ContextFramework", meta = (WorldContext="WorldContextObject",CustomStructureParam = "Value"))
	static void SetComponentOfContextId(const UObject* WorldContextObject,int32 ContextId, const int32& Value);
	
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "ContextFramework", meta = (WorldContext="WorldContextObject",CustomStructureParam = "Value"))
	static void SetComponent(const UObject* WorldContextObject,const int32& Value);


#pragma endregion



#pragma region "Set Component CPP"


	template<typename ComponentType>
	inline static void SetComponent(const UObject* WorldContextObject, ComponentType Component)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				CF_CoreSubSystem->SetComponent_Template<ComponentType>(GetContextId(WorldContextObject),Component);
			}
		}
	}
	
	
	template<typename ComponentType>
	inline static void SetComponentOfContextId(const UObject* WorldContextObject, int32 ContextId, ComponentType Component)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				CF_CoreSubSystem->SetComponent_Template<ComponentType>(ContextId,Component);
			}
		}
	}

	
#pragma endregion 





	
#pragma region "Remove Component CPP"
	
	template<typename ComponentType>
	inline static void RemoveComponentOfContextId(const UObject* WorldContextObject, int32 ContextId)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				CF_CoreSubSystem->RemoveComponent_Template<ComponentType>(ContextId);
			}
		}
	}


	template<typename ComponentType>
		inline static void RemoveComponent(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
			{
				CF_CoreSubSystem->RemoveComponent_Template<ComponentType>(GetContextId(WorldContextObject));
			}
		}
	}

	
#pragma endregion



#pragma region "Add Component BP"

	UFUNCTION(BlueprintCallable,Category="ContextFramework", meta=(WorldContext="WorldContextObject"))
	static void RemoveComponentFromContextId(const UObject* WorldContextObject, int32 ContextId, FInstancedStruct DummyTypeHoldingInstancedStruct);

	UFUNCTION(BlueprintCallable,Category="ContextFramework", meta=(WorldContext="WorldContextObject"))
	static void RemoveComponent(const UObject* WorldContextObject, FInstancedStruct DummyTypeHoldingInstancedStruct);

#pragma endregion




	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static bool IsForComponentOfType(const UObject* WorldContextObject, FInstancedStruct ComponentMessage, FString ComponentTypeName);

	inline static FString GetComponentTypeId(const UScriptStruct* ScriptStruct)
	{
		return ScriptStruct->GetName();
	}
	
	template<typename ComponentType>
	inline static FString GetComponentTypeId()
	{
		return ComponentType::StaticStruct()->GetName();
	}

	
private:

	DECLARE_FUNCTION(execGetComponentOfContextId);
	DECLARE_FUNCTION(execGetComponent);


	DECLARE_FUNCTION(execSetComponentOfContextId);
	DECLARE_FUNCTION(execSetComponent);
	


	
};

