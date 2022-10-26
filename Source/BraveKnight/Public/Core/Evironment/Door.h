// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsebleObject.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"


UCLASS()
class BRAVEKNIGHT_API ADoor : public AUsebleObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Doors logic")
		UBoxComponent* DoorCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Doors logic")
		class UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Doors logic")
		class UStaticMeshComponent* SwitchMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Doors logic")
		UBoxComponent* SwitchCollision;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Doors logic")
		float SwitchTime;

	UPROPERTY(BlueprintReadWrite, Category = "Doors logic")
		FTimerHandle SwitchHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector InitialDoorLocation;

	FVector InitialSwitchLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Doors logic")
	bool bIsDoorOpen;
	
	//FORCEINLINE bool GetIsDoorOpen() { return bIsDoorOpen; }
	//FORCEINLINE void SetIsDoorOpen(bool value) { bIsDoorOpen = value; }



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();


	UFUNCTION(BlueprintImplementableEvent)
	void CloseDoor();

	UFUNCTION(BlueprintCallable)
	void UpdateDoorLocation(float value);

	UFUNCTION(BlueprintCallable)
	void UpdateSwitchLocation(float value);


};
