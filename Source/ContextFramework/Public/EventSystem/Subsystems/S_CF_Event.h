// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/GameState/CF_WrapperGameState.h"
#include "UnrealGameplayFramework/ContextWrapper/BaseClasses/PlayerState/CF_WrapperPlayerState.h"
#include "UObject/Object.h"
#include "S_CF_Event.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum ENetworkMessageType
{
	None UMETA(DisplayName = "Local"),
	FromPlayerToServer UMETA(DisplayName = "FromPlayerToServer"),
	FromServerToPlayerBasedOnId   UMETA(DisplayName = "FromServerToPlayerBasedOnId"),
	FromServerToAllPlayers      UMETA(DisplayName = "FromServerToAllPlayers"),
};





DECLARE_MULTICAST_DELEGATE_TwoParams(FOnContextEvent,const UObject*,FInstancedStruct);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnContextEventDynamic,const UObject*,Invoker,FInstancedStruct,Message);










USTRUCT(BlueprintType)
struct CONTEXTFRAMEWORK_API FCF_DoubleMessageTypeDelegate 
{
	GENERATED_BODY()

	
	const UStruct* BaseMessageType;

	
	TMap<FString,FOnContextEvent> ContextEventDelegates = TMap<FString,FOnContextEvent>();


	FCF_DoubleMessageTypeDelegate()
	{
		BaseMessageType = nullptr;
		ContextEventDelegates = TMap<FString,FOnContextEvent>();
	}
	
	FCF_DoubleMessageTypeDelegate(const UStruct* _BaseMessageType)
	{
		BaseMessageType = _BaseMessageType;
		ContextEventDelegates = TMap<FString,FOnContextEvent>();
	}

	static void FireEvent(const UObject* Invoker,const FCF_DoubleMessageTypeDelegate& DoubleMessageTypeDelegate , const UStruct* SecondaryMessageType, FInstancedStruct Message)
	{
		if(DoubleMessageTypeDelegate.ContextEventDelegates.Contains(SecondaryMessageType->GetName()))
			DoubleMessageTypeDelegate.ContextEventDelegates[SecondaryMessageType->GetName()].Broadcast(Invoker,Message);
	}


	static FDelegateHandle AddLambda(FCF_DoubleMessageTypeDelegate& DoubleMessageTypeDelegate ,  UScriptStruct* SecondaryMessageType,const FOnContextEventDynamic& OnContextEvent)
	{
		if(!DoubleMessageTypeDelegate.ContextEventDelegates.Contains(SecondaryMessageType->GetName()))
			DoubleMessageTypeDelegate.ContextEventDelegates.Add(SecondaryMessageType->GetName(),FOnContextEvent());
		
		return DoubleMessageTypeDelegate.ContextEventDelegates[SecondaryMessageType->GetName()].AddLambda([&OnContextEvent](const UObject* Invoker,FInstancedStruct Message)
		{
			if(OnContextEvent.IsBound())
				OnContextEvent.Execute(Invoker,Message);
		});
	}


	template<typename BaseStructType,typename SecondaryStructType>
	static FDelegateHandle AddLambda(FCF_DoubleMessageTypeDelegate& DoubleMessageTypeDelegate ,TFunction<void(const UObject*,BaseStructType)> Lambda)
	{
		if(!DoubleMessageTypeDelegate.ContextEventDelegates.Contains(SecondaryStructType::StaticStruct()->GetName()))
			DoubleMessageTypeDelegate.ContextEventDelegates.Add(SecondaryStructType::StaticStruct()->GetName(),FOnContextEvent());
		
		return DoubleMessageTypeDelegate.ContextEventDelegates[SecondaryStructType::StaticStruct()->GetName()].AddLambda([Lambda](const UObject* Invoker,FInstancedStruct Message)
		{
			Lambda(Invoker,Message.Get<BaseStructType>());
		});
	}


	template<typename BaseStructType>
	static FDelegateHandle AddLambda(FCF_DoubleMessageTypeDelegate& DoubleMessageTypeDelegate ,UScriptStruct* SecondaryScriptStruct,TFunction<void(const UObject*,BaseStructType)> Lambda)
	{
		if(!DoubleMessageTypeDelegate.ContextEventDelegates.Contains(SecondaryScriptStruct->GetName()))
			DoubleMessageTypeDelegate.ContextEventDelegates.Add(SecondaryScriptStruct->GetName(),FOnContextEvent());
		return DoubleMessageTypeDelegate.ContextEventDelegates[SecondaryScriptStruct->GetName()].AddLambda([Lambda](const UObject* Invoker,FInstancedStruct Message)
		{
			Lambda(Invoker,Message.Get<BaseStructType>());
		});
	}
	


	
	template <typename SecondaryStructType>
	static bool RemoveLambda(FCF_DoubleMessageTypeDelegate& DoubleMessageTypeDelegate ,FDelegateHandle Handle)
	{
		if(DoubleMessageTypeDelegate.ContextEventDelegates.Contains(SecondaryStructType::StaticStruct()))
			return DoubleMessageTypeDelegate.ContextEventDelegates[SecondaryStructType::StaticStruct()].Remove(Handle);
		return false;
	}

	
	static bool RemoveLambda(FCF_DoubleMessageTypeDelegate& DoubleMessageTypeDelegate ,const UScriptStruct* SecondaryMessageScriptStruct,FDelegateHandle Handle)
	{
		if(DoubleMessageTypeDelegate.ContextEventDelegates.Contains(SecondaryMessageScriptStruct->GetName()))
			return DoubleMessageTypeDelegate.ContextEventDelegates[SecondaryMessageScriptStruct->GetName()].Remove(Handle);
		return false;
	}
	
	
};












UCLASS()
class CONTEXTFRAMEWORK_API US_CF_Event : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:


	TMap<FString,FCF_DoubleMessageTypeDelegate> DoubleMessageTypeContextEventDelegates = TMap<FString,FCF_DoubleMessageTypeDelegate>();


	TMap<FString,FOnContextEvent> ContextEventDelegates = TMap<FString,FOnContextEvent>();
	


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;




protected:




	virtual inline void FireEvent_Local(const UObject* Invoker,FInstancedStruct Message)
	{
		if(ContextEventDelegates.Contains(Message.GetScriptStruct()->GetName()))
			ContextEventDelegates[Message.GetScriptStruct()->GetName()].Broadcast(Invoker,Message);
	}


	virtual inline void FireEvent_Local(const UObject* Invoker,const UStruct* SecondaryMessageType,FInstancedStruct Message)
	{
		if(DoubleMessageTypeContextEventDelegates.Contains(Message.GetScriptStruct()->GetName()))
			FCF_DoubleMessageTypeDelegate::FireEvent(Invoker,DoubleMessageTypeContextEventDelegates[Message.GetScriptStruct()->GetName()],SecondaryMessageType,Message);
	}

	

	inline void FireEvent_Internal(const UObject* Invoker,FInstancedStruct MessageInstancedStruct,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		if(!Invoker)
			throw;
		
		//fire local version always
		
		FireEvent_Local(Invoker,MessageInstancedStruct);
		
		switch (NetworkMessageType)
		{
		case None:
			{
				break;
			}
		case FromPlayerToServer:
			{
				ACF_WrapperPlayerState* PlayerState = this->GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPlayerState<ACF_WrapperPlayerState>();
				PlayerState->FireEventOverNetwork_ToServer(MessageInstancedStruct);
				break;
			}
		case FromServerToPlayerBasedOnId:
			{
				const ACF_WrapperGameState* GameState = this->GetWorld()->GetGameState<ACF_WrapperGameState>();
				const TArray<APlayerState*> PlayerStates = GameState->PlayerArray;
				ACF_WrapperPlayerState* TargetPlayerState = nullptr;
				for (const auto PlayerState : PlayerStates)
				{
					if(PlayerState->GetPlayerId() == TargetPlayerId)
						TargetPlayerState = Cast<ACF_WrapperPlayerState>(PlayerState);
				}
				if(TargetPlayerState)
				{
					TargetPlayerState->FireEventOverNetwork_ToOwningClient(MessageInstancedStruct);
				}
				break;
			}
		case FromServerToAllPlayers:
			{
				ACF_WrapperGameState* GameState = this->GetWorld()->GetGameState<ACF_WrapperGameState>();
				GameState->FireEventOverNetwork_NetMulticast(MessageInstancedStruct);
				break;
			}
		default: ;
		}
	}



	inline void FireEvent_Internal(const UObject* Invoker,const UScriptStruct* SecondaryMessageScriptStruct,FInstancedStruct MessageInstancedStruct,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		if(!Invoker)
			throw;
		
		//fire local version always
		
		FireEvent_Local(Invoker,SecondaryMessageScriptStruct,MessageInstancedStruct);
		
		switch (NetworkMessageType)
		{
		case None:
			{
				break;
			}
		case FromPlayerToServer:
			{
				ACF_WrapperPlayerState* PlayerState = this->GetWorld()->GetGameInstance()->GetFirstLocalPlayerController()->GetPlayerState<ACF_WrapperPlayerState>();
				PlayerState->FireDoubleMessageTypeEventOverNetwork_ToServer(MessageInstancedStruct,SecondaryMessageScriptStruct);
				break;
			}
		case FromServerToPlayerBasedOnId:
			{
				const ACF_WrapperGameState* GameState = this->GetWorld()->GetGameState<ACF_WrapperGameState>();
				const TArray<APlayerState*> PlayerStates = GameState->PlayerArray;
				ACF_WrapperPlayerState* TargetPlayerState = nullptr;
				for (const auto PlayerState : PlayerStates)
				{
					if(PlayerState->GetPlayerId() == TargetPlayerId)
						TargetPlayerState = Cast<ACF_WrapperPlayerState>(PlayerState);
				}
				if(TargetPlayerState)
				{
					TargetPlayerState->FireDoubleMessageTypeEventOverNetwork_ToOwningClient(MessageInstancedStruct,SecondaryMessageScriptStruct);
				}
				break;
			}
		case FromServerToAllPlayers:
			{
				ACF_WrapperGameState* GameState = this->GetWorld()->GetGameState<ACF_WrapperGameState>();
				GameState->FireDoubleMessageTypeEventOverNetwork_NetMulticast(SecondaryMessageScriptStruct,MessageInstancedStruct);
				break;
			}
		default: ;
		}
	}
	


	

	
	
public:

	
	// Begin USubsystem
	// End USubsystem

	
	inline FDelegateHandle AddLambdaListener(const UScriptStruct* MessageScriptStruct,const FOnContextEventDynamic& OnContextEvent)
	{
		if(!ContextEventDelegates.Contains(MessageScriptStruct->GetName()))
			ContextEventDelegates.Add(MessageScriptStruct->GetName(),FOnContextEvent());
		
		return ContextEventDelegates[MessageScriptStruct->GetName()].AddLambda([OnContextEvent](const UObject* Invoker,FInstancedStruct InstancedStruct)
			{
				if(OnContextEvent.IsBound())
					OnContextEvent.Execute(Invoker,InstancedStruct);
			});
	}

	inline FDelegateHandle AddLambdaListener(const UScriptStruct* BaseMessageScriptStruct,UScriptStruct* SecondaryMessageScriptStruct,const FOnContextEventDynamic& OnContextEvent)
	{
		if(!DoubleMessageTypeContextEventDelegates.Contains(BaseMessageScriptStruct->GetName()))
			DoubleMessageTypeContextEventDelegates.Add(BaseMessageScriptStruct->GetName(),FCF_DoubleMessageTypeDelegate());
		
		return FCF_DoubleMessageTypeDelegate::AddLambda(DoubleMessageTypeContextEventDelegates[BaseMessageScriptStruct->GetName()],
			SecondaryMessageScriptStruct,OnContextEvent);
		
	}

	

	

	template <typename StructType>
	inline FDelegateHandle AddLambdaListener(TFunction<void(const UObject*,StructType)> Lambda)
	{
		if(!ContextEventDelegates.Contains(StructType::StaticStruct()->GetName()))
			ContextEventDelegates.Add(StructType::StaticStruct()->GetName(),FOnContextEvent());
		
		return ContextEventDelegates[StructType::StaticStruct()->GetName()].AddLambda([Lambda](const UObject* Invoker,FInstancedStruct InstancedStruct)
			{
				Lambda(Invoker,InstancedStruct.Get<StructType>());
			});

	}


	template <typename BaseStructType, typename SecondaryStructType>
	inline FDelegateHandle AddLambdaListener(TFunction<void(const UObject*,BaseStructType)> Lambda)
	{
		if(!DoubleMessageTypeContextEventDelegates.Contains(BaseStructType::StaticStruct()->GetName()))
			DoubleMessageTypeContextEventDelegates.Add(BaseStructType::StaticStruct()->GetName(),FCF_DoubleMessageTypeDelegate(BaseStructType::StaticStruct()));
		
		return FCF_DoubleMessageTypeDelegate::
		AddLambda<BaseStructType,SecondaryStructType>(
			DoubleMessageTypeContextEventDelegates[BaseStructType::StaticStruct()->GetName()],
			Lambda);

	}
	

	template <typename StructType>
	inline bool RemoveLambda(FDelegateHandle Handle)
	{
		if(ContextEventDelegates.Contains(StructType::StaticStruct()->GetName()))
			return ContextEventDelegates[StructType::StaticStruct()->GetName()].Remove(Handle);
		return false;
	}


	template <typename BaseStructType, typename SecondaryStructType>
	inline bool RemoveLambda(FDelegateHandle Handle)
	{
		if(!DoubleMessageTypeContextEventDelegates.Contains(BaseStructType::StaticStruct()->GetName()))
			return false;

		return FCF_DoubleMessageTypeDelegate::RemoveLambda<SecondaryStructType>(DoubleMessageTypeContextEventDelegates[BaseStructType::StaticStruct()->GetName()],Handle);
		
	}
	
	inline bool RemoveLambda(FDelegateHandle Handle, const UScriptStruct* BaseMessageScriptStruct,const UScriptStruct* SecondaryMessageScriptStruct)
	{

		if(!DoubleMessageTypeContextEventDelegates.Contains(BaseMessageScriptStruct->GetName()))
			return false;
		return FCF_DoubleMessageTypeDelegate::RemoveLambda(DoubleMessageTypeContextEventDelegates[BaseMessageScriptStruct->GetName()],SecondaryMessageScriptStruct,Handle);
	}
	
	
	inline bool RemoveLambda(FDelegateHandle Handle, const UScriptStruct* MessageScriptStruct)
	{
		if(ContextEventDelegates.Contains(MessageScriptStruct->GetName()))
		{
			return ContextEventDelegates[MessageScriptStruct->GetName()].Remove(Handle);
		}
		return false;
	}
	
	
	
	template <typename StructType>
	inline void FireEvent_Template(const UObject* Invoker,StructType Message,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		if(!Invoker)
			return;
		FInstancedStruct InstancedStructMessage;
		InstancedStructMessage.InitializeAs<StructType>(Message);
		FireEvent_Internal(Invoker,InstancedStructMessage,NetworkMessageType,TargetPlayerId);
		
	}


	template <typename BaseStructType, typename SecondaryStructType>
	inline void FireEvent_Template(const UObject* Invoker,BaseStructType Message,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		if(!Invoker)
			return;


			FInstancedStruct InstancedStructMessage;
			InstancedStructMessage.InitializeAs<BaseStructType>(Message);
			//FCF_DoubleMessageTypeDelegate::FireEvent(Invoker,DoubleMessageTypeContextEventDelegates[BaseStructType::StaticStruct()],SecondaryStructType::StaticStruct(),InstancedStructMessage);
			FireEvent_Internal(Invoker,SecondaryStructType::StaticStruct(),InstancedStructMessage,NetworkMessageType,TargetPlayerId);	
		
	}
	

	
	inline void FireEvent(const UObject* Invoker,const UScriptStruct* SecondaryMessageScriptStruct,FInstancedStruct MessageInstancedStruct,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		if(!Invoker)
			return;
		FireEvent_Internal(Invoker,SecondaryMessageScriptStruct,MessageInstancedStruct,NetworkMessageType,TargetPlayerId);
		
	}


	
	inline void FireEvent(const UObject* Invoker,FInstancedStruct Message,ENetworkMessageType NetworkMessageType = ENetworkMessageType::None, int32 TargetPlayerId = -1)
	{
		if(!Invoker)
			return;
		FireEvent_Internal(Invoker,Message,NetworkMessageType,TargetPlayerId);	
	}
	
	
};


