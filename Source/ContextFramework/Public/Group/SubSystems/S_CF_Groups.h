// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Core/Component/Messages/ComponentRemoved/CF_ComponentRemovedMessage.h"
#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "Group/Messages/GroupMemberAdded/CF_GroupMemberAddedMessage.h"
#include "Group/Messages/GroupMemberRemoved/CF_GroupMemberRemovedMessage.h"
#include "Group/Object/CF_Group.h"
#include "UObject/Object.h"
#include "S_CF_Groups.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API US_CF_Groups : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TMap<FString,FCF_Group> ActiveGroups = TMap<FString,FCF_Group>();

	UPROPERTY()
	TArray<FString> SortedComponentIds = TArray<FString>();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;


	


#pragma region "One Component Groups"
	
	template<typename ComponentType>
	bool ShouldContextBeInGroup_OneComponent(const int32 ContextId)
	{
		return UCF_Statics::HasComponentForContextId(this,ContextId,ComponentType::StaticStruct());
	}


	
	
	template<typename ComponentType>
	void AddContextToGroup_OneComponent(const int32 ContextId)
	{
		const FString GroupId = GetGroupId_OneComponent<ComponentType>();
		if(!ActiveGroups[GroupId].Contexts.Contains(ContextId))
		{
			ActiveGroups[GroupId].Contexts.Add(ContextId);
			UCF_EventStatics::FireEvent_Template<FCF_GroupMemberAddedMessageBase,ComponentType>(this,FCF_GroupMemberAddedMessageBase(ContextId));
		}
		
		
	}
	template<typename ComponentType>
	void RemoveContextFromGroup_OneComponent(const int32 ContextId)
	{
		const FString GroupId = GetGroupId_OneComponent<ComponentType>();
		ActiveGroups[GroupId].Contexts.Remove(ContextId);
		UCF_EventStatics::FireEvent_Template<FCF_GroupMemberRemovedMessageBase,ComponentType>(this,FCF_GroupMemberRemovedMessageBase(ContextId));
	}
	
	template<typename ComponentType>
	inline void InitializeGroup_OneComponent()
	{
		const FString GroupId = GetGroupId_OneComponent<ComponentType>();
		const FCF_Group CF_Group = FCF_Group();
		ActiveGroups.Add(GroupId,CF_Group);

		const TArray<FCF_Context>& Contexts = UCF_Statics::GetContexts(this);
		for (int i = 0; i < Contexts.Num(); ++i)
		{
			if(UCF_Statics::HasComponentForContextId(this,Contexts[i].ContextId,ComponentType::StaticStruct()))
				ActiveGroups[GroupId].Contexts.Add(Contexts[i].ContextId);
		}


		UCF_EventStatics::AddLambdaListener<FCF_ComponentSetMessageBase,ComponentType>(this,[this](const UObject* Invoker,FCF_ComponentSetMessageBase ComponentAddedMessage)
	{
		OnComponentType1Set_OneComponent<ComponentType>(Invoker,ComponentAddedMessage);
	});

		
		
		UCF_EventStatics::AddLambdaListener<FCF_ComponentSetMessageBase,ComponentType>(this,[this](const UObject* Invoker,FCF_ComponentSetMessageBase ComponentAddedMessage)
		{
			OnComponentType1Added_OneComponent<ComponentType>(Invoker,ComponentAddedMessage);
		});

		UCF_EventStatics::AddLambdaListener<FCF_ComponentRemovedMessageBase,ComponentType>(this,[this](const UObject* Invoker,FCF_ComponentRemovedMessageBase ComponentRemovedMessage)
		{
			OnComponentType1Removed_OneComponent<ComponentType>(Invoker,ComponentRemovedMessage);
		});
	}

	template<typename ComponentType>
	inline void OnComponentType1Set_OneComponent(const UObject* Invoker,FCF_ComponentSetMessageBase ComponentAddedMessage)
	{
		if(ShouldContextBeInGroup_OneComponent<ComponentType>(ComponentAddedMessage.ContextId))
			AddContextToGroup_OneComponent<ComponentType>(ComponentAddedMessage.ContextId);
	}

	
	template<typename ComponentType>
	inline void OnComponentType1Added_OneComponent(const UObject* Invoker,FCF_ComponentSetMessageBase ComponentAddedMessage)
	{
		if(ShouldContextBeInGroup_OneComponent<ComponentType>(ComponentAddedMessage.ContextId))
			AddContextToGroup_OneComponent<ComponentType>(ComponentAddedMessage.ContextId);
	}
	template<typename ComponentType>
	inline void OnComponentType1Removed_OneComponent(const UObject* Invoker,FCF_ComponentRemovedMessageBase ComponentRemovedMessage)
	{
		if(!ShouldContextBeInGroup_OneComponent<ComponentType>(ComponentRemovedMessage.ContextId))
			RemoveContextFromGroup_OneComponent<ComponentType>(ComponentRemovedMessage.ContextId);
	}



	template<typename ComponentType>
	inline  TArray<FCF_Context> GetGroupContexts_OneComponent()
	{
		const FString GroupId = GetGroupId_OneComponent<ComponentType>();
		if(!ActiveGroups.Contains(GroupId))
		{
			InitializeGroup_OneComponent<ComponentType>();
		}
		return UCF_Statics::GetContextsForIds(this,ActiveGroups[GroupId].Contexts);
	}
	
	
	template<typename ComponentType>
	inline const TArray<int32>& GetGroupContextIds_OneComponent()
	{
		const FString GroupId = GetGroupId_OneComponent<ComponentType>();
		if(!ActiveGroups.Contains(GroupId))
		{
			InitializeGroup_OneComponent<ComponentType>();
		}
		return ActiveGroups[GroupId].Contexts;
	}


	static FString GetGroupId(TArray<UScriptStruct*> ComponentTypes)
	{
		ComponentTypes.Sort();
		FString GroupId = "";
		for (const auto ComponentType : ComponentTypes)
		{
			GroupId.Append(ComponentType->GetName());
		}
		return GroupId;
	}
	
	static inline FString GetGroupId_OneComponent(const UScriptStruct* ComponentType)
	{
		return ComponentType->GetName();
	}

	
	template<typename ComponentType>
	FString GetGroupId_OneComponent()
	{
		return ComponentType::StaticStruct()->GetName();
	}

#pragma endregion 

	

	template<typename ComponentType, typename ComponentType2>
	FString GetGroupId()
	{
		SortedComponentIds.Empty();
		SortedComponentIds.Add(
			ComponentType::StaticStruct()->GetName(),
			ComponentType2::StaticStruct()->GetName());
		SortedComponentIds.Sort();
		FString GroupId = "";
		for (const auto SortedComponent: SortedComponentIds)
		{
			GroupId.Append(SortedComponent);
		}
		return GroupId;
	}


	template<typename ComponentType, typename ComponentType2, typename ComponentType3>
	FString GetGroupId()
	{
		SortedComponentIds.Empty();
		SortedComponentIds.Add(
			ComponentType::StaticStruct()->GetName(),
			ComponentType2::StaticStruct()->GetName(),
			ComponentType3::StaticStruct()->GetName());
		SortedComponentIds.Sort();
		FString GroupId = "";
		for (const auto SortedComponent: SortedComponentIds)
		{
			GroupId.Append(SortedComponent);
		}
		return GroupId;
	}

	
	
};

