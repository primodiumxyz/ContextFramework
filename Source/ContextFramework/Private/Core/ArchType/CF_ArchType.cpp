#include "Core/ArchType/CF_ArchType.h"
#include "Core/Context/CF_Context.h"

FCF_ArchType::FCF_ArchType(const FCF_Context& Context)
{
		InitialComponents = TArray<FInstancedStruct>();
		for (auto Component : Context.Components)
		{
			FInstancedStruct InitialComponent;
			InitialComponent.InitializeAs(Component.Value.GetScriptStruct(),Component.Value.GetMemory());
			InitialComponents.Add(InitialComponent);
		}

}
