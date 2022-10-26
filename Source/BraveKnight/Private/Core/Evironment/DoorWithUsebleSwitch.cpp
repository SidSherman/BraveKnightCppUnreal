// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Evironment/DoorWithUsebleSwitch.h"

ADoorWithUsebleSwitch::ADoorWithUsebleSwitch()
{


}

// Called when the game starts or when spawned
void ADoorWithUsebleSwitch::BeginPlay()
{
	Super::BeginPlay();
	// Bind On Overlap methods

}

// Called every frame
void ADoorWithUsebleSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ADoorWithUsebleSwitch::UseObject()
{

	Super::UseObject();

	if (!bIsDoorOpen)
	{
		OpenDoor();
	}

	if (bIsDoorOpen)
	{
		CloseDoor();
	}
	
}