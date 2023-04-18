// Fill out your copyright notice in the Description page of Project Settings.


#include "ContextFramework/Public/Core/Subsystems/S_CF_Core.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "EventSystem/Message/CF_Message.h"

FCF_Context& US_CF_Core::GetContextInternal(int32 ContextId)
{
	if(ContextId == -1 || InActiveContexts.Contains(ContextId) || Contexts.Num() <= ContextId)
	{
		return UCF_Statics::InvalidContext;
	}
	return Contexts[ContextId];
}

const FCF_Context& US_CF_Core::CreateNewContextInternal()
{
	int32 AvailableContextId;
	if(!InActiveContexts.IsEmpty())
	{
		AvailableContextId = InActiveContexts.Pop();
		Contexts[AvailableContextId].Components.Empty();
	}
	else
	{
		AvailableContextId = GetNewContextId();
		Contexts.Add(FCF_Context(AvailableContextId));
	}
	return Contexts[AvailableContextId];
}

void US_CF_Core::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Super::Initialize(Collection);
	Contexts = TArray<FCF_Context>();
}

int32 US_CF_Core::GetNewContextId() const
{
	return Contexts.Num();
}

bool US_CF_Core::SetContextAsInActive(int32 ContextId)
{
	if(!InActiveContexts.Contains(ContextId))
	{
		InActiveContexts.Add(ContextId);
		return true;
	}
	return false;
}

const TArray<FCF_Context>& US_CF_Core::GetContexts()
{
	return Contexts;
}

const FCF_Context& US_CF_Core::GetContext(int32 ContextId)
{
	if(ContextId == -1 || InActiveContexts.Contains(ContextId) || Contexts.Num() <= ContextId)
	{
		return UCF_Statics::InvalidContext;
	}
	return Contexts[ContextId];
}

bool US_CF_Core::HasComponent(int32 ContextId, const UScriptStruct* ComponentType)
{
	return Contexts[ContextId].Components.Contains(ComponentType->GetName());
}

const FInstancedStruct& US_CF_Core::GetComponent(int32 ContextId, const  UScriptStruct* ComponentType)
{
	return GetComponentFromStringId(ContextId,ComponentType->GetName());
}

const FInstancedStruct& US_CF_Core::GetComponentFromStringId(int32 ContextId, FString ComponentType)
{
	const FCF_Context& Context = GetContext(ContextId);
	if(Context.IsValid)
	{
		if(Contexts[ContextId].Components.Contains(ComponentType))
			return Contexts[ContextId].Components[ComponentType];
	}
	return UCF_Statics::InvalidComponent;
}

void US_CF_Core::SetComponent(int32 ContextId, FInstancedStruct Component)
{
	FCF_Context& Context = GetContextInternal(ContextId);
	if(Context.IsValid)
	{
		if(HasComponent(ContextId,Component.GetScriptStruct()))
			FCF_Context::SetComponent(Context,Component);
		else
			FCF_Context::AddComponent(Context,Component);
	
		FCF_ComponentSetMessageBase ComponentSetMessage =FCF_ComponentSetMessageBase(ContextId,Component.GetScriptStruct()); 
		FInstancedStruct ComponentSetMessageInstancedStruct ;
		ComponentSetMessageInstancedStruct .InitializeAs<FCF_ComponentSetMessageBase>(ComponentSetMessage);
		UCF_EventStatics::FireDoubleMessageTypeEvent_InstancedStruct(this,Component.GetScriptStruct(),ComponentSetMessageInstancedStruct);
	}
}

void US_CF_Core::RemoveComponent(int32 ContextId, const UScriptStruct* ComponentType)
{
	FCF_Context& Context = GetContextInternal(ContextId);

	{
		FCF_ComponentRemovedMessageBase ComponentRemovedMessage =FCF_ComponentRemovedMessageBase(ContextId,ComponentType); 
		FInstancedStruct ComponentRemovedMessageInstancedStruct ;
		ComponentRemovedMessageInstancedStruct .InitializeAs<FCF_ComponentRemovedMessageBase>(ComponentRemovedMessage);
		UCF_EventStatics::FireDoubleMessageTypeEvent_InstancedStruct(this,ComponentType,ComponentRemovedMessageInstancedStruct);
	}
	
	if(Context.IsValid)
		Context.Components.Remove(ComponentType->GetName());

	
}


const FCF_Context& US_CF_Core::CreateNewContext()
{
	int32 AvailableContextId;
	if(!InActiveContexts.IsEmpty())
	{
		AvailableContextId = InActiveContexts.Pop();
		Contexts[AvailableContextId].Components.Empty();
	}
	else
	{
		AvailableContextId = GetNewContextId();
		Contexts.Add(FCF_Context(AvailableContextId));
	}
	return Contexts[AvailableContextId];
}

// FCF_Context* UCF_CoreSubsystem::CreateNewContextPointer()
// {
// 	int32 AvailableContextId;
// 	if(!InActiveContexts.IsEmpty())
// 	{
// 		AvailableContextId = InActiveContexts.Pop();
// 		Contexts[AvailableContextId].Components.Empty();
// 	}
// 	else
// 	{
// 		AvailableContextId = GetNewContextId();
// 		Contexts.Add(FCF_Context(AvailableContextId));
// 	}
// 	return &Contexts.GetData()[AvailableContextId];
// }


const FCF_Context& US_CF_Core::CreateNewContextFrom(const FCF_Context& FromContext)
{
	int32 AvailableContextId;
	if(!InActiveContexts.IsEmpty())
	{
		AvailableContextId = InActiveContexts.Pop();
	}
	else
	{
		AvailableContextId = GetNewContextId();
		Contexts.Add(FCF_Context(AvailableContextId));
	}
	CopyComponentsFromContext(FromContext,AvailableContextId);
	return Contexts[AvailableContextId];
}

const FCF_Context& US_CF_Core::CreateNewContextFromArchtype(const FCF_ArchType FromArchType)
{
	int32 AvailableContextId;
	if(!InActiveContexts.IsEmpty())
	{
		AvailableContextId = InActiveContexts.Pop();
	}
	else
	{
		AvailableContextId = GetNewContextId();
		Contexts.Add(FCF_Context(AvailableContextId));
	}
	CopyComponentsFromArchtype(FromArchType,AvailableContextId);
	return Contexts[AvailableContextId];
}

void US_CF_Core::CopyComponentsFromContext(const FCF_Context& FromContext, int32 ToContextId)
{
	for (const auto FromComponent : FromContext.Components)
	{
		SetComponent(ToContextId,FromComponent.Value);
	}
}

void US_CF_Core::CopyComponentsFromArchtype(const FCF_ArchType& FromArchType, int32 ToContextId)
{
	for (const auto FromComponent : FromArchType.InitialComponents)
	{
		SetComponent(ToContextId,FromComponent);
	}
}

void US_CF_Core::ReturnContext(const int32 ContextId)
{
	while (Contexts[ContextId].Components.Num() > 0)
	{
		TArray<const UScriptStruct*> ComponentsToRemove =TArray<const UScriptStruct*>();
		for (auto ToRemoveComponent : Contexts[ContextId].Components)
		{
			ComponentsToRemove.Add(ToRemoveComponent.Value.GetScriptStruct());
		}
		for (const auto ToRemove : ComponentsToRemove)
		{
			RemoveComponent(ContextId,ToRemove);
		}
	}
	InActiveContexts.Add(ContextId);
}
