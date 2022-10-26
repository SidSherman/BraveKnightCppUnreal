// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class BRAVEKNIGHT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
		class UBoxComponent* SpawnZone;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		TSubclassOf<class APawn> SpawningPawn;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Spawner")
		FVector GetSpawnPoint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawner")
		void SpawnPawn(UClass* SpawnPawn, const FVector& Location);


};
