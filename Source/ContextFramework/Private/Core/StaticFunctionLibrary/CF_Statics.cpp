// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/StaticFunctionLibrary/CF_Statics.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Kismet/GameplayStatics.h"


#define LOCTEXT_NAMESPACE "UCF_Statics"



#pragma region "Create Context"

const FCF_Context& UCF_Statics::CreateNewContext(const UObject* WorldContextObject)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return CF_CoreSubSystem->CreateNewContext();
		}
	}
	//throw;
	return InvalidContext;
}

const FCF_Context& UCF_Statics::CreateNewContextFrom(const UObject* WorldContextObject, const FCF_Context From)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return  CF_CoreSubSystem->CreateNewContextFrom(From);
		}
	}
	//throw;
	return InvalidContext;
	// FCF_Context InValidContext = FCF_Context(false); 
	// return InValidContext;
}

const FCF_Context& UCF_Statics::CreateNewContextFromArchType(const UObject* WorldContextObject, const FCF_ArchType From)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return  CF_CoreSubSystem->CreateNewContextFromArchtype(From);
		}
	}
	//throw;
	return InvalidContext;
	// FCF_Context InValidContext = FCF_Context(false); 
	// return InValidContext;
}


#pragma endregion


#pragma region "Context Utility"




const FCF_Context& UCF_Statics::GetContextForId(const UObject* WorldContextObject, int32 ContextId)
{

	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return  CF_CoreSubSystem->GetContext(ContextId);
		}
	}
	//throw;
	return InvalidContext;
	// FCF_Context InValidContext = FCF_Context(false); 
	// return InValidContext;
}

const FCF_Context& UCF_Statics::GetContext(const UObject* WorldContextObject)
{
	const int32 ContextId = GetContextId(WorldContextObject);
	if( ContextId != -1)
	{
		return GetContextForId(WorldContextObject,ContextId);	
	}
	return InvalidContext; 
}





int32 UCF_Statics::GetContextId(const UObject* WorldContextObject)
{
	
	const UObject* Outer = WorldContextObject;
	while (Outer && !Outer->Implements<UCF_Wrapper>())
	{
		Outer = Outer->GetOuter();
	}
	if(Outer && Outer->Implements<UCF_Wrapper>())
	{
		const ICF_Wrapper* Wrapper = Cast<ICF_Wrapper>(Outer);
		return Wrapper->GetContextId();
	}
	else
	{
		return -1;
	}
}

bool UCF_Statics::HasComponent(const UObject* WorldContextObject, UScriptStruct* ScriptStruct)
{
	return HasComponentForContextId(WorldContextObject,GetContextId(WorldContextObject),ScriptStruct);
	
}


bool UCF_Statics::HasComponentForContextId(const  UObject* WorldContextObject, int32 ContextId, UScriptStruct* ScriptStruct)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return  CF_CoreSubSystem->HasComponent(ContextId,ScriptStruct);
		}
	}
	return false;
}


void UCF_Statics::ReturnContextId(const UObject* WorldContextObject, int32 ContextId)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			CF_CoreSubSystem->ReturnContext(ContextId);
		}
	}
}

const TArray<FCF_Context>& UCF_Statics::GetContexts(const UObject* WorldContextObject)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return CF_CoreSubSystem->GetContexts();
		}
	}
	static const TArray<FCF_Context> EmptyArray = TArray<FCF_Context>();
	return EmptyArray;
}

TArray<FCF_Context> UCF_Statics::GetContextsForIds(const UObject* WorldContextObject,
	const TArray<int32>& ContextIds)
{
	TArray<FCF_Context> Contexts =TArray<FCF_Context>();
	Contexts.SetNum(ContextIds.Num());
	for (int i = 0; i < ContextIds.Num(); ++i)
	{
		Contexts[i] = GetContextForId(WorldContextObject,ContextIds[i]);
	}
	return Contexts;
	
}


#pragma endregion

// void UCF_Statics::GetComponentOfType(const  UObject* WorldContextObject, UScriptStruct* ComponentClass,
//                                      UStruct* OutComponent)
// {
// }



void UCF_Statics::RemoveComponentFromContextId(const UObject* WorldContextObject, int32 ContextId,
	FInstancedStruct DummyTypeHoldingInstancedStruct)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			if(DummyTypeHoldingInstancedStruct.IsValid())
				CF_CoreSubSystem->RemoveComponent(ContextId,DummyTypeHoldingInstancedStruct.GetScriptStruct());
		}
	}
}

void UCF_Statics::RemoveComponent(const UObject* WorldContextObject, FInstancedStruct DummyTypeHoldingInstancedStruct)
{
	RemoveComponentFromContextId(WorldContextObject,GetContextId(WorldContextObject),DummyTypeHoldingInstancedStruct);
}

bool UCF_Statics::IsForComponentOfType(const UObject* WorldContextObject, FInstancedStruct ComponentMessage,
                                       FString ComponentTypeName)
{
	return ComponentMessage.Get<FCF_ComponentMessageBase>().ComponentType->GetName().Equals(ComponentTypeName);
}

const FInstancedStruct& UCF_Statics::GetComponentInstancedStructOfContextId(const UObject* WorldContextObject, int32 ContextId,const UScriptStruct* ScriptStruct)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			return  CF_CoreSubSystem->GetComponent(ContextId,ScriptStruct);
		}
	}
	return InvalidComponent;
}

const FInstancedStruct& UCF_Statics::GetComponentInstancedStruct(const UObject* WorldContextObject, const UScriptStruct* ScriptStruct)
{
	return GetComponentInstancedStructOfContextId(WorldContextObject,GetContextId(WorldContextObject),ScriptStruct);
}

void UCF_Statics::SetComponentInstancedStructOfContextId(const UObject* WorldContextObject, int32 ContextId,
	FInstancedStruct Component)
{
	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	{
		if(US_CF_Core* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Core>())
		{
			if(Component.IsValid())
				CF_CoreSubSystem->SetComponent(ContextId,Component);
			else
				throw;
		}
	}
}

void UCF_Statics::SetComponentInstancedStruct(const UObject* WorldContextObject, FInstancedStruct Component)
{
	SetComponentInstancedStructOfContextId(WorldContextObject,GetContextId(WorldContextObject),Component);
}



void UCF_Statics::SetComponentOfContextId(const  UObject* WorldContextObject,int32 ContextId,const int32& Value)
{
	checkNoEntry();
}

void UCF_Statics::SetComponent(const  UObject* WorldContextObject, const int32& Value)
{
	checkNoEntry();
}

void UCF_Statics::GetComponentOfContextId(const  UObject* WorldContextObject, ECF_GetComponentResult& ExecResult,
                                          int32 ContextId, int32& Value)
{
	checkNoEntry();
}

void UCF_Statics::GetComponent(const  UObject* WorldContextObject, ECF_GetComponentResult& ExecResult, int32& Value)
{
	checkNoEntry();
}

DEFINE_FUNCTION(UCF_Statics::execSetComponent)
{
	//Stack.Step(Stack.Object, nullptr);

	
	P_GET_OBJECT(UObject,WorldContextObject);


	
	

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	
	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	const void* ValuePtr = Stack.MostRecentPropertyAddress;

	FInstancedStruct ComponentInstancedStruct;
	P_FINISH;

	if (!ValueProp || !ValuePtr)
	{
		FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("ContextFramework_AddInvalidComponent", "Failed to resolve the Value for Add Component")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);

		P_NATIVE_BEGIN;
		ComponentInstancedStruct.Reset();
		P_NATIVE_END;
	}
	else
	{
		P_NATIVE_BEGIN;
		ComponentInstancedStruct.InitializeAs(ValueProp->Struct, (const uint8*)ValuePtr);
		SetComponentInstancedStruct(WorldContextObject,ComponentInstancedStruct);
		P_NATIVE_END;
	}
}


DEFINE_FUNCTION(UCF_Statics::execSetComponentOfContextId)
{
	//Stack.Step(Stack.Object, nullptr);


	P_GET_OBJECT(UObject,WorldContextObject);
	P_GET_UBOOL32(ContextId);

	
	

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	
	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	const void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;

	FInstancedStruct ComponentInstancedStruct;
	if (!ValueProp || !ValuePtr)
	{
		FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("ContextFramework_AddInvalidComponentToContextId", "Failed to resolve the Value for Add Component To ContextId")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);

		P_NATIVE_BEGIN;
		ComponentInstancedStruct.Reset();
		P_NATIVE_END;
	}
	else
	{
		ComponentInstancedStruct.InitializeAs(ValueProp->Struct, (const uint8*)ValuePtr);
		SetComponentInstancedStructOfContextId(WorldContextObject,ContextId,ComponentInstancedStruct);
	}
}

//
// DEFINE_FUNCTION(UCF_Statics::execAddComponent)
// {
// 	//Stack.Step(Stack.Object, nullptr);
//
//
// 	P_GET_OBJECT(UObject,WorldContextObject);
//
//
// 	
// 	
//
// 	Stack.MostRecentPropertyAddress = nullptr;
// 	Stack.MostRecentPropertyContainer = nullptr;
// 	Stack.StepCompiledIn<FStructProperty>(nullptr);
// 	
// 	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
// 	const void* ValuePtr = Stack.MostRecentPropertyAddress;
//
// 	P_FINISH;
//
// 	FInstancedStruct ComponentInstancedStruct;
// 	if (!ValueProp || !ValuePtr)
// 	{
// 		FBlueprintExceptionInfo ExceptionInfo(
// 			EBlueprintExceptionType::AbortExecution,
// 			LOCTEXT("ContextFramework_AddInvalidComponent", "Failed to resolve the Value for Add Component")
// 		);
//
// 		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
//
// 		P_NATIVE_BEGIN;
// 		ComponentInstancedStruct.Reset();
// 		P_NATIVE_END;
// 	}
// 	else
// 	{
// 		ComponentInstancedStruct.InitializeAs(ValueProp->Struct, (const uint8*)ValuePtr);
// 		AddComponentInstancedStruct(WorldContextObject,ComponentInstancedStruct);
// 	}
// }
//
//
// DEFINE_FUNCTION(UCF_Statics::execAddComponentToContextId)
// {
// 	//Stack.Step(Stack.Object, nullptr);
//
//
// 	P_GET_OBJECT(UObject,WorldContextObject);
// 	P_GET_UBOOL32(ContextId);
//
// 	
// 	
//
// 	Stack.MostRecentPropertyAddress = nullptr;
// 	Stack.MostRecentPropertyContainer = nullptr;
// 	Stack.StepCompiledIn<FStructProperty>(nullptr);
// 	
// 	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
// 	const void* ValuePtr = Stack.MostRecentPropertyAddress;
//
// 	P_FINISH;
//
// 	FInstancedStruct ComponentInstancedStruct;
// 	if (!ValueProp || !ValuePtr)
// 	{
// 		FBlueprintExceptionInfo ExceptionInfo(
// 			EBlueprintExceptionType::AbortExecution,
// 			LOCTEXT("ContextFramework_AddInvalidComponentToContextId", "Failed to resolve the Value for Add Component To ContextId")
// 		);
//
// 		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
//
// 		P_NATIVE_BEGIN;
// 		ComponentInstancedStruct.Reset();
// 		P_NATIVE_END;
// 	}
// 	else
// 	{
// 		ComponentInstancedStruct.InitializeAs(ValueProp->Struct, (const uint8*)ValuePtr);
// 		AddComponentInstancedStructOfContextId(WorldContextObject,ContextId,ComponentInstancedStruct);
// 	}
// }
//

DEFINE_FUNCTION(UCF_Statics::execGetComponentOfContextId)
{
	P_GET_OBJECT(UObject,WorldContextObject);
	P_GET_ENUM_REF(ECF_GetComponentResult, ExecResult);
	P_GET_UBOOL32(ContextId);

	

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);

	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;
	ExecResult = ECF_GetComponentResult::NotValid;
	if (!ValueProp || !ValuePtr)
	{
		FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("ContextFramework_GetComponentInvalid", "Failed to resolve the Value for Get Component ")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}
	else
	{
		const FInstancedStruct& ComponentInstancedStruct = GetComponentInstancedStructOfContextId(WorldContextObject,ContextId,ValueProp->Struct);
		P_NATIVE_BEGIN;
		if (ComponentInstancedStruct.IsValid() && ComponentInstancedStruct.GetScriptStruct()->IsChildOf(ValueProp->Struct))
		{
			ValueProp->Struct->CopyScriptStruct(ValuePtr, ComponentInstancedStruct.GetMemory());
			ExecResult = ECF_GetComponentResult::Valid;
		}
		else
		{
			ExecResult = ECF_GetComponentResult::NotValid;
		}
		P_NATIVE_END;
	}
}
DEFINE_FUNCTION(UCF_Statics::execGetComponent)
{
	P_GET_OBJECT(UObject,WorldContextObject);
	P_GET_ENUM_REF(ECF_GetComponentResult, ExecResult);
	

	

	Stack.MostRecentPropertyAddress = nullptr;
	Stack.MostRecentPropertyContainer = nullptr;
	Stack.StepCompiledIn<FStructProperty>(nullptr);
	
	const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	P_FINISH;
	ExecResult = ECF_GetComponentResult::NotValid;
	if (!ValueProp || !ValuePtr)
	{
		FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AbortExecution,
			LOCTEXT("ContextFramework_GetComponentForContextIdInvalid", "Failed to resolve the Value for Get Component For ContextId")
		);

		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}
	else
	{
		const FInstancedStruct& ComponentInstancedStruct = GetComponentInstancedStruct(WorldContextObject,ValueProp->Struct);
		P_NATIVE_BEGIN;
		if (ComponentInstancedStruct.IsValid() && ComponentInstancedStruct.GetScriptStruct()->IsChildOf(ValueProp->Struct))
		{
			ValueProp->Struct->CopyScriptStruct(ValuePtr, ComponentInstancedStruct.GetMemory());
			ExecResult = ECF_GetComponentResult::Valid;
		}
		else
		{
			ExecResult = ECF_GetComponentResult::NotValid;
		}
		P_NATIVE_END;
	}
}


#undef LOCTEXT_NAMESPACE