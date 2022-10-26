// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Evironment/UsebleObject.h"

// Sets default values
AUsebleObject::AUsebleObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUsebleObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUsebleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUsebleObject::UseObject()
{
	UE_LOG(LogTemp, Warning, TEXT("UseObject"));
}