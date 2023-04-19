// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGameplayFramework/ContextWrapper/Subsystems/SpawnContextWrapperInstanceFromType/S_CF_SpawnContextWrapperInstanceFromType.h"

#include "Core/Component/Messages/ComponentSet/CF_ComponentSetMessage.h"
#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "EventSystem/StaticFuntionLibrary/CF_EventStatics.h"
#include "EventSystem/Subsystems/S_CF_Event.h"
#include "UnrealGameplayFramework/ContextWrapper/Components/ContextWrapperInstance/C_CF_ContextWrapperInstance.h"
#include "UnrealGameplayFramework/ContextWrapper/Components/ContextWrapperType/C_CF_ContextWrapperType.h"
#include "UnrealGameplayFramework/PoolManager/Subsystems/S_CF_PoolManager.h"

void US_CF_SpawnContextWrapperInstanceFromType::Initialize(FSubsystemCollectionBase& Collection)
{
	
	Collection.InitializeDependency(US_CF_PoolManager::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Super::Initialize(Collection);


	UCF_EventStatics::AddLambdaListener<FCF_ComponentSetMessageBase, FC_CF_ContextWrapperType>(this,[this](const UObject* Invoker,FCF_ComponentSetMessageBase ContextWrapperTypeSet)
	{
		OnContextWrapperTypeComponentSet(Invoker,ContextWrapperTypeSet);
	});

}

bool US_CF_SpawnContextWrapperInstanceFromType::ShouldCreateSubsystem(UObject* Outer) const
{
	return !Cast<UGameInstance>(Outer)->GetWorldContext()->RunAsDedicated;
}


void US_CF_SpawnContextWrapperInstanceFromType::OnContextWrapperTypeComponentSet(const UObject* Invoker,
                                                                                 FCF_ComponentSetMessageBase ContextWrapperTypeSet)
{
	const int32 ContextId = ContextWrapperTypeSet.ContextId;
	const FC_CF_ContextWrapperType ContextWrapperType = UCF_Statics::GetComponentOfContextId<FC_CF_ContextWrapperType>(this,ContextId); 
	ACF_WrapperActor* ContextWrapperActor =  GetGameInstance()->GetSubsystem<US_CF_PoolManager>()->GetNewInstanceOf(ContextWrapperType.ContextWrapperType);

	if(ContextWrapperActor == nullptr)
		return;
	
	const FC_CF_ContextWrapperInstance ContextWrapperInstance =FC_CF_ContextWrapperInstance(ContextWrapperActor);
	UCF_Statics::SetComponentOfContextId<FC_CF_ContextWrapperInstance>(this,ContextId,ContextWrapperInstance);
	ContextWrapperActor->SetContextId(ContextId);


	
	
	
}
