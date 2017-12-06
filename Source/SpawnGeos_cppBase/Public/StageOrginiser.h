// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeoUnit.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "SpawnGeos_cppBaseGameMode.h"
#include "StageOrginiser.generated.h"

UCLASS()
class SPAWNGEOS_CPPBASE_API AStageOrginiser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageOrginiser();

	UPROPERTY(EditAnywhere)
		UBoxComponent* Frame_Box;				// box frame which all elemnts are spawn into it

	UPROPERTY(EditAnywhere)
		int	Maximum_Elements_to_Spawn = 240;	// max number of elements to spawn

	UPROPERTY(EditAnywhere)
		FString	Orginiser_Ident = "Orgimizer A";	// Identity of spawner class 

	void SpawnElement();						// elemnt spawner function

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// elemetns 
	int			Element_Counter = 0;			// count spawned elements on stage
	float		Frame_Box_Scale = 3.2f;			// default box frame for spawn elements
	FVector		Element_Boundries = FVector::OneVector * Frame_Box_Scale;	// Element box boundries vector	
	
	// control
	bool		Control_Activate = false;				// activate spawn functionality
	ASpawnGeos_cppBaseGameMode* Control_gamemode;		// current game mode used for deligate event
};
