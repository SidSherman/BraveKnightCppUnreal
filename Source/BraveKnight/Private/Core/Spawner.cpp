// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Spawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
//#include "Engine/World.h"
//#include "Runtime/Engine/Classes/Components/ActorComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnZone"));


}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawner::GetSpawnPoint() {

	FVector SpawnExtend = SpawnZone->GetScaledBoxExtent();
	FVector SpawnOrigin = SpawnZone->GetComponentLocation();

	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtend);

	return Point;


}

// Virtual function that can be overrided in BP
void ASpawner::SpawnPawn_Implementation(UClass* SpawnPawn, const FVector& Location)
{

	if (SpawnPawn)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParameter;
			APawn* SpawnedPawn = World->SpawnActor<APawn>(SpawnPawn, Location, FRotator(0.f), SpawnParameter);;
		}
	}
}