// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "SpawnGeos_cppBaseGameMode.h"
#include "GeoUnit.generated.h"

UCLASS()
class SPAWNGEOS_CPPBASE_API AGeoUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeoUnit();
		
	UPROPERTY(EditAnywhere)
		UBoxComponent* Element_Box;						// element collision box
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Element_Mesh = nullptr;	// element static mesh

	// collision function 
	UFUNCTION()
		void OnPickedup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	void SetUp(int id, float scale, float RandomTreshold);					// setup & refresh Element scale
	void Activate(bool Destroyable, ASpawnGeos_cppBaseGameMode* gamemode, FString Orginizer_indent);	// activate destroy functionality and delegate event

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Control variables
	FString			Control_ParentOrginizer = "";		// Orginizer class identity
	bool			Control_MeshAdded = false;			// Check for add mesh
	ACharacter*		Control_VisitorObject = NULL;		// Use for detect character in collision funtion
	bool			Control_Destroyable = false;		// set destroy enable/disable
	ASpawnGeos_cppBaseGameMode* Control_gamemode;		// current game mode used for deligate event
	
	// Element variables
	int			Element_ID = 0;							// element ID number
	float		Element_Scale = 0.5f;					// scale value 
	float		Element_Scale_RandomTreshold = 0.5f;	// scale Treshold max value

	FVector		Element_Boundries = FVector(1.0f, 1.0f, 1.0f);	// Element box boundries vector
	const float Element_CollisionTreshold = 1.72f;				// additional treshold on boundries for collision detection



	void Refresh();				// update new boundries on Elements
	int getGeoData();			// get Element id (TODO: get full details) 

	void Element_init();		// setup elements box and static mesh with position and scale
	void Element_Destroy();		// remove element and fire delegate event in game mode
	
};
