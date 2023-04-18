// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ArchType/CF_ArchType.h"
#include "Core/Component/Messages/ComponentRemoved/CF_ComponentRemovedMessage.h"
#include "Core/Component/Messages/ComponentSet/CF_ComponentSetMessage.h"
#include "Core/Context/CF_Context.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "S_CF_Core.generated.h"

/**
 * 
 */
UCLASS()
class CONTEXTFRAMEWORK_API US_CF_Core : public UGameInstanceSubsystem
{
	GENERATED_BODY()



protected:
	
	FCF_Context& GetContextInternal(int32 ContextId);
	
	
	const FCF_Context& CreateNewContextInternal();


	
public:




	UPROPERTY()
	TArray<int32> InActiveContexts;

	UPROPERTY()
	TArray<FCF_Context> Contexts;

	

	
	

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY()
	int32 ComponentTypeIdCounter = 0;

	

	UFUNCTION()
	int32 GetNewContextId() const;
	

	UFUNCTION()
	bool SetContextAsInActive(int32 ContextId);

	
	UFUNCTION()
	const TArray<FCF_Context>& GetContexts();

	UFUNCTION()
	const FCF_Context& GetContext(int32 ContextId);

	UFUNCTION()
	bool HasComponent(int32 ContextId,const UScriptStruct* ComponentType);

	UFUNCTION()
	const FInstancedStruct& GetComponent(int32 ContextId, const UScriptStruct* ComponentType);

	UFUNCTION()
	const FInstancedStruct& GetComponentFromStringId(int32 ContextId, FString ComponentType);
	
	UFUNCTION()
	void SetComponent(int32 ContextId, FInstancedStruct Component);



	
	UFUNCTION()
	void RemoveComponent(int32 ContextId, const UScriptStruct* ComponentType);

	


	template<typename ComponentType>
	bool HasComponent(int32 ContextId)
	{
		return Contexts[ContextId].Components.Contains(ComponentType::StaticStruct()->GetName());
	}

	

	template<typename ComponentType>
	inline void SetComponent_Template(int32 ContextId, ComponentType Component)
	{
		FCF_Context& Context = GetContextInternal(ContextId);
		const auto ComponentId =ComponentType::StaticStruct()->GetName(); 
		
		FInstancedStruct ComponentInstancedStruct;
		ComponentInstancedStruct.InitializeAs<ComponentType>(Component);
		SetComponent(ContextId,ComponentInstancedStruct);	
	}

	template<typename T>
	inline const T& GetComponent_Template(int32 ContextId)
	{
		return GetComponent(ContextId,T::StaticStruct()).template GetMutable<T>();
	}


	template<typename ComponentType>
	inline void RemoveComponent_Template(int32 ContextId)
	{
		RemoveComponent(ContextId,ComponentType::StaticStruct());
		//UCF_EventStatics::FireEvent_Template<FCF_ComponentRemovedMessageBase,ComponentType>(this,FCF_ComponentRemovedMessageBase(ContextId,ComponentType::StaticStruct()));
	}
	

	// UFUNCTION()
	// FCF_Context* CreateNewContextPointer();
	
	
	UFUNCTION()
	const FCF_Context& CreateNewContext();

	UFUNCTION()
	const FCF_Context& CreateNewContextFrom(const FCF_Context& FromContext);

	UFUNCTION()
	const FCF_Context& CreateNewContextFromArchtype(const FCF_ArchType FromArchType);



	UFUNCTION()
	void CopyComponentsFromContext(const FCF_Context& FromContext, int32 ToContextId);


	UFUNCTION()
	void CopyComponentsFromArchtype(const FCF_ArchType& FromArchType, int32 ToContextId);
	

	

	UFUNCTION()
	void ReturnContext(const int32 ContextId);

	
	

	

};
