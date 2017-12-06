// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SpawnGeos_cppBaseGameMode.h"
#include "SpawnGeos_cppBaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpawnGeos_cppBaseGameMode::ASpawnGeos_cppBaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Destroy event
	Unit_Detroyed.BindUObject(this, &ASpawnGeos_cppBaseGameMode::Destruction_Method);
}

// Destroy Event
void ASpawnGeos_cppBaseGameMode::Destruction_Method(FString data, FVector location)
{
	// TODO: add GeoParticle element at location and  ... ; ] ,, 
	////// .... 


	UE_LOG(LogTemp, Warning, TEXT("%s - destroyed at --- %s"), *data, *location.ToString() );
	
	/*
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
			FString(" ID: "				).
			Append(FString::FromInt(id)	).
			Append("   --- at:   "		).
			Append(location.ToString()	)
	);
	*/
}
