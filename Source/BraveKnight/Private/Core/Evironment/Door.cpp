// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Evironment/Door.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create switch mesh and collision

	SwitchMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("SwitchMesh"));
	SwitchCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SwitchCollision"));
	RootComponent = SwitchCollision;
	
	SwitchMesh->SetupAttachment(GetRootComponent());



	// Create door mesh and collision
	DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
	DoorMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorCollision->SetupAttachment(GetRootComponent());
	DoorMesh->SetupAttachment(DoorCollision);
	

	

	//Set collision settings
	SwitchCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SwitchCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SwitchCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SwitchCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	

	bIsDoorOpen = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	// Bind On Overlap methods


	InitialDoorLocation = DoorCollision->GetComponentLocation();
	InitialSwitchLocation = SwitchCollision->GetComponentLocation();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





void ADoor::UpdateDoorLocation(float value)
{
	FVector NewLocation = InitialDoorLocation;
	NewLocation.Z += value;
	DoorCollision->SetWorldLocation(NewLocation);
}

void ADoor::UpdateSwitchLocation(float value)
{
	FVector NewLocation = InitialSwitchLocation;
	NewLocation.Z += value;
	DoorCollision->SetWorldLocation(NewLocation);
}
