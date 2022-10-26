// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Evironment/DoorWithPressureSwitch.h"

// Sets default values
ADoorWithPressureSwitch::ADoorWithPressureSwitch()
{

	SwitchTime = 3.0f;

}

// Called when the game starts or when spawned
void ADoorWithPressureSwitch::BeginPlay()
{
	Super::BeginPlay();
	// Bind On Overlap methods

}

// Called every frame
void ADoorWithPressureSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SwitchCollision->OnComponentBeginOverlap.AddDynamic(this, &ADoorWithPressureSwitch::OnOverlapBegin);
	SwitchCollision->OnComponentEndOverlap.AddDynamic(this, &ADoorWithPressureSwitch::OnOverlapEnd);
}




void ADoorWithPressureSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32  OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SwitchHandle.IsValid())
	{
		SwitchHandle.Invalidate();
	}

	//UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));

	if (!bIsDoorOpen)
	{
		OpenDoor();
	}
	
}

void ADoorWithPressureSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32  OtherBodyIndex)
{
	if (SwitchHandle.IsValid())
	{
		SwitchHandle.Invalidate();
	}

	if (bIsDoorOpen)
	{
		GetWorldTimerManager().SetTimer(SwitchHandle, this, &ADoor::CloseDoor, SwitchTime);
	}
		
}
