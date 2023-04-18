// Fill out your copyright notice in the Description page of Project Settings.


#include "Group/SubSystems/S_CF_Groups.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "EventSystem/Subsystems/S_CF_Event.h"

void US_CF_Groups::Initialize(FSubsystemCollectionBase& Collection)
{
	
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Super::Initialize(Collection);
}
