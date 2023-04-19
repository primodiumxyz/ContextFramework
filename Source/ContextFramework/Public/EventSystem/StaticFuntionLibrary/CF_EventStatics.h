// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "EventSystem/DelegateHandle/CF_DelegateHandle.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "CF_EventStatics.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API UCF_EventStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
 

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static FCF_DelegateHandle AddLambdaListener(UObject* WorldContextObject,UScriptStruct* MessageScriptStruct, const FOnContextEventDynamic& OnContextEvent);


	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static bool RemoveLambdaListener(UObject* WorldContextObject, const FCF_DelegateHandle& CF_DelegateHandle);

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "Invoker" ))
	static void FireEvent_InstancedStruct(const UObject* Invoker,FInstancedStruct MessageInstancedStruct,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1);

	UFUNCTION(BlueprintCallable,CustomThunk, Category="ContextFramework", meta = (WorldContext = "Invoker",CustomStructureParam = "Value" ))
	static void FireEvent(const UObject* Invoker,const int32& Value,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1);



	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static FCF_DelegateHandle AddDoubleMessageTypeLambdaListener(UObject* WorldContextObject,UScriptStruct* MessageScriptStruct,UScriptStruct* SecondaryMessageScriptStruct, const FOnContextEventDynamic& OnContextEvent);


	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject"))
	static bool RemoveDoubleMessageTypeLambdaListener(UObject* WorldContextObject, UScriptStruct* SecondaryMessageScriptStruct,const FCF_DelegateHandle& CF_DelegateHandle);

	UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "Invoker" ))
	static void FireDoubleMessageTypeEvent_InstancedStruct(const UObject* Invoker,const UScriptStruct* SecondaryMessageScriptStruct,FInstancedStruct MessageInstancedStruct,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1);

	UFUNCTION(BlueprintCallable,CustomThunk, Category="ContextFramework", meta = (WorldContext = "Invoker",CustomStructureParam = "Value" ))
	static void FireDoubleMessageTypeEvent(const UObject* Invoker,UScriptStruct* SecondaryMessageScriptStruct,const int32& Value,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1);
	

	

	// UFUNCTION(BlueprintCallable, Category="ContextFramework", meta = (WorldContext = "WorldContextObject", ))
	// static FDelegateHandle AddLambdaListenerSubClass(UObject* WorldContextObject,TSubclassOf<UScriptStruct> MessageScriptStruct, FOnContextEvent& OnContextEvent);


	template <typename StructType>
	inline static FDelegateHandle AddLambdaListener(UObject* WorldContextObject,TFunction<void(const UObject*,StructType)> Lambda)
	{
		return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<US_CF_Event>()->AddLambdaListener<StructType>(Lambda);
	}

	template <typename StructType>
	inline static bool RemoveLambda(UObject* WorldContextObject,FDelegateHandle Handle)
	{
		return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<US_CF_Event>()->RemoveLambda<StructType>(Handle);
	}


	template <typename StructType>
	inline static void FireEvent_Template(const UObject* Invoker,StructType Message,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		UGameplayStatics::GetGameInstance(Invoker)->GetSubsystem<US_CF_Event>()->FireEvent_Template<StructType>(Invoker,Message,NetworkMessageType,TargetPlayerId);
	}


	template <typename StructType, typename SecondaryStructType>
	inline static FDelegateHandle AddLambdaListener(UObject* WorldContextObject,TFunction<void(const UObject*,StructType)> Lambda)
	{
		return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<US_CF_Event>()->AddLambdaListener<StructType,SecondaryStructType>(Lambda);
	}

	template <typename StructType, typename SecondaryStructType>
	inline static void RemoveLambda(UObject* WorldContextObject,FDelegateHandle Handle)
	{
		UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<US_CF_Event>()->RemoveLambda<StructType,SecondaryStructType>(Handle);
	}


	template <typename StructType, typename SecondaryStructType>
	inline static void FireEvent_Template(const UObject* Invoker,StructType Message,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		UGameplayStatics::GetGameInstance(Invoker)->GetSubsystem<US_CF_Event>()->FireEvent_Template<StructType,SecondaryStructType>(Invoker,Message,NetworkMessageType,TargetPlayerId);
	}
	

	DECLARE_FUNCTION(execFireEvent);
	DECLARE_FUNCTION(execFireDoubleMessageTypeEvent);
	
	
};
