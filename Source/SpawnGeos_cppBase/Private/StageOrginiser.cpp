// Fill out your copyright notice in the Description page of Project Settings.

#include "StageOrginiser.h"


// Sets default values
AStageOrginiser::AStageOrginiser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set up fame box and scale
	Frame_Box = CreateDefaultSubobject<UBoxComponent>("Element Box");
	RootComponent = Frame_Box;
	Frame_Box->SetWorldScale3D(Element_Boundries);
}

void AStageOrginiser::SpawnElement()
{
	//UE_LOG(LogTemp, Warning, TEXT(" ---- spawning ---- "));
	if (Element_Counter < Maximum_Elements_to_Spawn) {
		Element_Counter++;
		
		// spawn element
		AGeoUnit* GeoSample = GetWorld()->SpawnActor<AGeoUnit>(AGeoUnit::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		
		// setup element
		if (GeoSample != nullptr) {
			if (UKismetMathLibrary::RandomBool()) {
				GeoSample->SetUp(Element_Counter, 0.1f, 0.5f);
			}
			else {
				GeoSample->SetUp(Element_Counter, 0.5f, 1.4f);
			}
			(GeoSample->GetRootComponent())->AttachToComponent(Frame_Box, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			// random location inside frame box
			FVector temp = UKismetMathLibrary::RandomPointInBoundingBox(Frame_Box->Bounds.Origin, Frame_Box->Bounds.BoxExtent);
			GeoSample->SetActorLocation(temp);
			// random size inside frame box
			float scale = UKismetMathLibrary::RandomFloatInRange(.1f, 1.0f);
			GeoSample->SetActorScale3D(FVector(scale, scale, scale));
			
			// add gamemode to elements and Activate them by setting Destroyable to true
			GeoSample->Activate(true, Control_gamemode, Orginiser_Ident);
		}
	}
	else {
		Control_Activate = false;
	}
}

// Called when the game starts or when spawned
void AStageOrginiser::BeginPlay()
{
	Super::BeginPlay();
	
	// reset element counter
	Element_Counter = 0;
	
	// setup game mode and activate spawn functionality by setting Control_Activate to true
	UWorld* World = GetWorld();
	if (World != nullptr) {
		Control_gamemode = Cast<ASpawnGeos_cppBaseGameMode>(UGameplayStatics::GetGameMode(World));
		if (Control_gamemode != nullptr) Control_Activate = true;
	}
	
	//////// spawn elements based on time frame
	/*
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AStageOrginiser::SpawnElement, 1.0f, true);
	*/
}

// Called every frame
void AStageOrginiser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Control_Activate) SpawnElement(); // spawn elements on tick

}

