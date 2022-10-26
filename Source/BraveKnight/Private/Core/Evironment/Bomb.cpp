// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PlayerCharacter.h"
#include "Core/Evironment/Bomb.h"

ABomb::ABomb()
{
	Damage = 0;
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::UseObject()
{

	Super::UseObject();
}



void ABomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

	if (Character)
	{

		Character->SetHealth(-Damage);
		UseObject();
	}

}

void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


}
