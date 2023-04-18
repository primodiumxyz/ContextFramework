// Fill out your copyright notice in the Description page of Project Settings.


#include "EventSystem/Subsystems/S_CF_Event.h"



void US_CF_Event::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ContextEventDelegates = TMap<FString,FOnContextEvent>();
}

void US_CF_Event::Deinitialize()
{
	Super::Deinitialize();
}