// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoUnit.h"


// Sets default values
AGeoUnit::AGeoUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// setup box and static mesh
	Element_init();
}

// Called when the game starts or when spawned
void AGeoUnit::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGeoUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////////

// creat box frame and static mesh using default values at start
void AGeoUnit::Element_init() {

	//setup box and assign collision function
	Element_Box = CreateDefaultSubobject<UBoxComponent>("Element Box");
	Element_Box->OnComponentBeginOverlap.AddDynamic(this, &AGeoUnit::OnPickedup);

	// setup mesh and apply scales and positioning
	Element_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Element Mesh");
	static ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("StaticMesh'/Game/Geos/Sphere.Sphere'"));
	if (tempMesh.Object) {
		Element_Mesh->SetStaticMesh(tempMesh.Object);
		Element_Mesh->SetMobility(EComponentMobility::Movable);
		Element_Mesh->SetRelativeLocation(FVector::ZeroVector);
		Element_Box->SetWorldScale3D(Element_Boundries + Element_CollisionTreshold);
		Element_Box->AttachToComponent(Element_Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		if (Element_Mesh) {
			Element_Mesh->SetWorldScale3D(Element_Boundries);
			Control_MeshAdded = true;		// mesh is loaded and added to stage
		}
		SetRootComponent(Element_Mesh);
	}
}

// on collision with specified visitor object, calls destroy function
void AGeoUnit::OnPickedup(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter != nullptr) {
		if (OtherCharacter == Control_VisitorObject) {
			//UE_LOG(LogTemp, Warning, TEXT(" - picked --- %s"), *(FString::FromInt(Element_ID)) );
			OtherCharacter->DestroyConstructedComponents();
			Element_Destroy();
		}
	}
}

// apply scales, locations and set controler variables. At the end calls Refresh
void AGeoUnit::SetUp(int id, float scale, float RandomTreshold) {
	
	// element data
	Element_ID = id;
	Element_Scale = scale;
	Element_Scale_RandomTreshold = RandomTreshold;

	// generate random boundries based on input data 
	Element_Boundries = FVector(
		FMath::RandRange(Element_Scale, Element_Scale + Element_Scale_RandomTreshold)
	);

	// update element
	Refresh();
}

// apply new scales to box and mesh
void AGeoUnit::Refresh() {
	if (Control_MeshAdded) {
		Element_Box->SetWorldScale3D(Element_Boundries + Element_CollisionTreshold);
		Element_Mesh->SetWorldScale3D(Element_Boundries);
	}
}

// destroy this object 
void AGeoUnit::Element_Destroy() {
	if (Control_Destroyable) {
		if (Control_gamemode != nullptr) {
			// activate delegate event in game mode by sending id and location of this object
			Control_gamemode->Unit_Detroyed.ExecuteIfBound(
				Control_ParentOrginizer.Append(" - id: ").Append(FString::FromInt(Element_ID)), Element_Box->GetComponentLocation()
			);
		}
		Destroy();
	}
}

// activate control variables
void AGeoUnit::Activate(bool Destroyable, ASpawnGeos_cppBaseGameMode* gamemode, FString Orginizer_indent) {
	Control_ParentOrginizer = Orginizer_indent; // base class identity which spawned this element
	Control_VisitorObject	= UGameplayStatics::GetPlayerCharacter(this, 0); // setup visitor object	
	Control_Destroyable		= Destroyable;		// delegate event activation
	Control_gamemode		= gamemode;			// game mode object setup
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: get object data 
int AGeoUnit::getGeoData() {
	return Element_ID;
}