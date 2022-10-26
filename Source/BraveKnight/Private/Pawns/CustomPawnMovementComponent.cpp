// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/CustomPawnMovementComponent.h"

void UCustomPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)

{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// return normalized Value from AddInmputVector
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0);


	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult HitResult;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, HitResult);
		// sweep means that we going to use HitResult and slide along


		// if we bump then we slide along 
		if (HitResult.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - HitResult.Time, HitResult.Normal, HitResult);
		}
	}
}