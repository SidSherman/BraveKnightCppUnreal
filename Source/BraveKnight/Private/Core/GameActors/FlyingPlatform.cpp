// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameActors/FlyingPlatform.h"
#include "TimerManager.h"

// Sets default values
AFlyingPlatform::AFlyingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	LocationTolerance = 10.0f;
	bShouldRepeatEndlessly = true;
	bShouldFly = true;
	FlyingSpeed = 1.0f;
	PauseTime = 0.0f;
	bShouldInterp = false;
	
	bSwitchToggle = true;
	

}

// Called when the game starts or when spawned
void AFlyingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (!FlyingPoints.IsEmpty())
	{
		CurrentPoint = FlyingPoints[0];
		CurrentPointIndex = 0;
	}
	
}

// Called every frame
void AFlyingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldFly)
	{

		if (!FlyingPoints.IsEmpty())
		{
			if (GetDistanceTo(CurrentPoint) > LocationTolerance)
			{



				FVector CurrentLocation = GetActorLocation();

				if (bShouldInterp)
				{
					FVector Interp = FMath::VInterpTo(CurrentLocation, CurrentPoint->GetActorLocation(), DeltaTime, FlyingSpeed);
					SetActorLocation(Interp);
					
				}
				else
				{
					FVector NewLocation = CurrentLocation + (CurrentPoint->GetActorLocation() - CurrentLocation).GetUnsafeNormal() * DeltaTime * FlyingSpeed;
					SetActorLocation(NewLocation);
				}

				

			}
			else if (bShouldRepeatEndlessly || (FlyingPoints.Num() - 1 != CurrentPointIndex))
			{
				if (PauseTime > 0)
				{
					if (bSwitchToggle)
					{
						GetWorldTimerManager().SetTimer(PauseTimer, this, &AFlyingPlatform::PointSelectorToggle, PauseTime);
						bSwitchToggle = false;
					}
				}
				else
				{
					PointSelector(CurrentPointIndex + 1);
				}
				//PointSelector(CurrentPointIndex + 1);
			}

			//UE_LOG(LogTemp, Warning, TEXT("Distance to point is %f"), GetDistanceTo(CurrentPoint));

		}
	}
	

}


void AFlyingPlatform::PointSelectorToggle()
{
	PointSelector(CurrentPointIndex + 1);
	bSwitchToggle = true;
}

// Set new target point for movement
void AFlyingPlatform::PointSelector(int NewIndex)
{
	if (!FlyingPoints.IsEmpty())
	{
		if (FlyingPoints.IsValidIndex(NewIndex))
		{
			CurrentPointIndex = NewIndex;

		}
		else
		{
			CurrentPointIndex = 0;
		}

		CurrentPoint = FlyingPoints[CurrentPointIndex];
	}
	else
	{
		CurrentPoint = NULL;
		CurrentPointIndex = 0;
	}

}

