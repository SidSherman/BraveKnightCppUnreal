// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Evironment/Door.h"
#include "DoorWithUsebleSwitch.generated.h"

/**
 * 
 */
UCLASS()
class BRAVEKNIGHT_API ADoorWithUsebleSwitch : public ADoor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ADoorWithUsebleSwitch();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void UseObject() override;

};


