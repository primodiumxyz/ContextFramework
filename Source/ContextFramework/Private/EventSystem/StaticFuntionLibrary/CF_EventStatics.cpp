// Fill out your copyright notice in the Description page of Project Settings.


#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"


FCF_DelegateHandle UCF_EventStatics::AddLambdaListener(UObject* WorldContextObject, UScriptStruct* MessageScriptStruct,
	const FOnContextEventDynamic& OnContextEvent) 
{
	
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(const auto CF_EventSubSystem = GameInstance->GetSubsystem<US_CF_Event>())
		{
			return FCF_DelegateHandle(CF_EventSubSystem->AddLambdaListener(MessageScriptStruct,OnContextEvent), MessageScriptStruct);
		}
	}
	return FCF_DelegateHandle();
}



bool UCF_EventStatics::RemoveLambdaListener(UObject* WorldContextObject,
                                            const FCF_DelegateHandle& CF_DelegateHandle)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		if(const auto CF_EventSubSystem = GameInstance->GetSubsystem<US_CF_Event>())
			if(CF_DelegateHandle.MessageScriptStruct != nullptr)
				return CF_EventSubSystem->RemoveLambda(CF_DelegateHandle.DelegateHandle,CF_DelegateHandle.MessageScriptStruct);
	return false;
}

void UCF_EventStatics::FireEvent_InstancedStruct(const UObject* Invoker, FInstancedStruct MessageInstancedStruct,
	ENetworkMessageType NetworkMessageType, int32 TargetPlayerId)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(Invoker))
		if(const auto CF_EventSubSystem = GameInstance->GetSubsystem<US_CF_Event>())
			CF_EventSubSystem->FireEvent(Invoker,MessageInstancedStruct,NetworkMessageType,TargetPlayerId);
}



void UCF_EventStatics::FireEvent(const UObject* Invoker, const int32& Value, ENetworkMessageType NetworkMessageType,
	int32 TargetPlayerId)
{
	checkNoEntry()
}

FCF_DelegateHandle UCF_EventStatics::AddDoubleMessageTypeLambdaListener(UObject* WorldContextObject, UScriptStruct* MessageScriptStruct,
	UScriptStruct* SecondaryMessageScriptStruct, const FOnContextEventDynamic& OnContextEvent)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(const auto CF_EventSubSystem = GameInstance->GetSubsystem<US_CF_Event>())
		{
			return FCF_DelegateHandle(CF_EventSubSystem->AddLambdaListener(MessageScriptStruct,SecondaryMessageScriptStruct,OnContextEvent), MessageScriptStruct);
		}
	}
	return FCF_DelegateHandle();
}

bool UCF_EventStatics::RemoveDoubleMessageTypeLambdaListener(UObject* WorldContextObject, UScriptStruct* SecondaryMessageScriptStruct,
	const FCF_DelegateHandle& CF_DelegateHandle)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		if(const auto CF_EventSubSystem = GameInstance->GetSubsystem<US_CF_Event>())
			if(CF_DelegateHandle.MessageScriptStruct != nullptr)
				return CF_EventSubSystem->RemoveLambda(CF_DelegateHandle.DelegateHandle,CF_DelegateHandle.MessageScriptStruct,SecondaryMessageScriptStruct);
	return false;
}

void UCF_EventStatics::FireDoubleMessageTypeEvent_InstancedStruct(const UObject* Invoker,const  UScriptStruct* SecondaryMessageScriptStruct,
	FInstancedStruct MessageInstancedStruct, ENetworkMessageType NetworkMessageType, int32 TargetPlayerId)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(Invoker))
		if(const auto CF_EventSubSystem = GameInstance->GetSubsystem<US_CF_Event>())
			CF_EventSubSystem->FireEvent(Invoker,SecondaryMessageScriptStruct,MessageInstancedStruct,NetworkMessageType,TargetPlayerId);
}

void UCF_EventStatics::FireDoubleMessageTypeEvent(const UObject* Invoker, UScriptStruct* SecondaryMessageScriptStruct,
	const int32& Value, ENetworkMessageType NetworkMessageType, int32 TargetPlayerId)
{
	checkNoEntry()
}

#define LOCTEXT_NAMESPACE "UStructUtilsFunctionLibrary"

DEFINE_FUNCTION(UCF_EventStatics::execFireEvent)
{
	//Stack.Step(Stack.Object, nullptr);

	P_GET_OBJECT(UObject,Invoker);


	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	
	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	const void* ValuePtr = Stack.MostRecentPropertyAddress;

	
	P_GET_ENUM_REF(ENetworkMessageType, NetworkMessageType);
	P_GET_UBOOL32(TargetPlayerId);
	


	P_FINISH;

	FInstancedStruct InstancedStructMessage;
	if (!ValueProp || !ValuePtr)
	{
		FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("InstancedStruct_MakeInvalidValueWarning", "Failed to resolve the Value for Make Instanced Struct")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);

		P_NATIVE_BEGIN;
		InstancedStructMessage.Reset();
		P_NATIVE_END;
	}
	else
	{
		P_NATIVE_BEGIN;
		InstancedStructMessage.InitializeAs(ValueProp->Struct, (const uint8*)ValuePtr);
		FireEvent_InstancedStruct(Invoker,InstancedStructMessage,NetworkMessageType,TargetPlayerId);
		P_NATIVE_END;
	}
}


DEFINE_FUNCTION(UCF_EventStatics::execFireDoubleMessageTypeEvent)
{
	//Stack.Step(Stack.Object, nullptr);

	P_GET_OBJECT(UObject,Invoker);


	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	
	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	const void* ValuePtr = Stack.MostRecentPropertyAddress;

	
	P_GET_ENUM_REF(ENetworkMessageType, NetworkMessageType);
	P_GET_UBOOL32(TargetPlayerId);
	


	P_FINISH;

	FInstancedStruct InstancedStructMessage;
	if (!ValueProp || !ValuePtr)
	{
		FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("InstancedStruct_MakeInvalidValueWarning", "Failed to resolve the Value for Make Instanced Struct")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);

		P_NATIVE_BEGIN;
		InstancedStructMessage.Reset();
		P_NATIVE_END;
	}
	else
	{
		P_NATIVE_BEGIN;
		InstancedStructMessage.InitializeAs(ValueProp->Struct, (const uint8*)ValuePtr);
		FireEvent_InstancedStruct(Invoker,InstancedStructMessage,NetworkMessageType,TargetPlayerId);
		P_NATIVE_END;
	}
}



#undef LOCTEXT_NAMESPACE