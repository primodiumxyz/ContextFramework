// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "CF_GroupsStatics.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API UCF_GroupsStatics : public UBlueprintFunctionLibrary
{

public:
	GENERATED_BODY()



	template<typename ComponentType>
	inline static const ComponentType& GetSingletonComponent(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				const TArray<int32> GroupContexts =CF_CoreSubSystem->GetGroupContextIds_OneComponent<ComponentType>();
				if(GroupContexts.Num() == 1)
					return UCF_Statics::GetComponentOfContextId<ComponentType>(WorldContextObject,GroupContexts[0]);
			}
		}
		throw;
	}

	template<typename ComponentType>
	inline static int32 GetSingletonComponentContextId(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				const TArray<int32> GroupContexts =CF_CoreSubSystem->GetGroupContextIds_OneComponent<ComponentType>();
				if(GroupContexts.Num() == 1)
					return GroupContexts[0];
			}
		}
		throw;
	}


	template<typename ComponentType, typename SingletonComponent>
	inline static void SetSingletonComponent(const UObject* WorldContextObject, const ComponentType Component)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				const TArray<int32> GroupContexts =CF_CoreSubSystem->GetGroupContextIds_OneComponent<SingletonComponent>();
				if(GroupContexts.Num() == 1)
				{
					UCF_Statics::SetComponentOfContextId<ComponentType>(WorldContextObject,GroupContexts[0],Component);
					return;
				}
				else
				{
					int32 num = GroupContexts.Num();
					++num;
					int32 a = num;
					auto Initial =TArray<FInstancedStruct>();
					Initial.SetNum(a);
					const FCF_ArchType Arch = FCF_ArchType(Initial); 
					UCF_Statics::CreateNewContextFromArchType(WorldContextObject,Arch);
					throw;
				}
			}
		}
		throw;
	}

	template<typename ComponentType>
	inline static void SetSingletonComponent(const UObject* WorldContextObject, const ComponentType Component)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				const TArray<int32> GroupContexts =CF_CoreSubSystem->GetGroupContextIds_OneComponent<ComponentType>();
				if(GroupContexts.Num() == 1)
				{
					UCF_Statics::SetComponentOfContextId<ComponentType>(WorldContextObject,GroupContexts[0],Component);
					return;
				}
			}
		}
		throw;
	}

	


	template<typename ComponentType>
	inline static void RemoveSingletonComponent(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				const TArray<int32> GroupContexts =CF_CoreSubSystem->GetGroupContextIds_OneComponent<ComponentType>();
				if(GroupContexts.Num() == 1)
				{
					UCF_Statics::RemoveComponentOfContextId<ComponentType>(WorldContextObject,GroupContexts[0]);
					return;
				}
			}
		}
		throw;
	}



	

	template<typename ComponentType>
	inline static bool DoesSingletonComponentExist(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				const TArray<int32> GroupContexts =CF_CoreSubSystem->GetGroupContextIds_OneComponent<ComponentType>();
				return GroupContexts.Num() == 1;			
			}
		}
		return false;
	}


	
	
	

	template<typename ComponentType>
	inline static const TArray<int32>& GetGroupContextIds(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				return  CF_CoreSubSystem->GetGroupContextIds_OneComponent<ComponentType>();
			}
		}
		static const TArray<int32> EmptyList = TArray<int32>(); 
		return EmptyList;
	}


	template<typename ComponentType>
	inline static  TArray<FCF_Context> GetGroupContexts(const UObject* WorldContextObject)
	{
		if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			if(US_CF_Groups* CF_CoreSubSystem = GameInstance->GetSubsystem<US_CF_Groups>())
			{
				return  CF_CoreSubSystem->GetGroupContexts_OneComponent<ComponentType>();
			}
		}
		static const TArray<FCF_Context> EmptyList = TArray<FCF_Context>(); 
		return EmptyList;
	}


	

	// template<typename ComponentType>
	// inline static const TArray<FCF_GroupObject>& GetGroups(const UObject* WorldContextObject)
	// {
	// 	if(const auto GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
	// 	{
	// 		if(UCF_GroupsSubSystem* CF_CoreSubSystem = GameInstance->GetSubsystem<UCF_GroupsSubSystem>())
	// 		{
	// 			return  CF_CoreSubSystem->GetGroupContexts_OneComponent<ComponentType>();
	// 		}
	// 	}
	// 	static const TArray<int32> EmptyList = TArray<int32>(); 
	// 	return EmptyList;
	// }


	
};
