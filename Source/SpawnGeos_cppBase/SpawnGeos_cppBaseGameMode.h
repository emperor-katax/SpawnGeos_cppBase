// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpawnGeos_cppBaseGameMode.generated.h"

DECLARE_DELEGATE_TwoParams(UnitEvent, FString, FVector); // event on destroy each element

UCLASS(minimalapi)
class ASpawnGeos_cppBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpawnGeos_cppBaseGameMode();

	// Destroy Event
	UnitEvent Unit_Detroyed;
	void Destruction_Method(FString data, FVector location);
};



