// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Evironment/Item.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AItem::AItem()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(SphereCollision);
	StaticMesh->SetupAttachment(GetRootComponent());
	bShouldUseOnOverlap = false;


	IdleParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticlesComponent"));
	IdleParticle->SetupAttachment(GetRootComponent());

}




// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	// Bind On Overlap methods

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::UseObject()
{

	Super::UseObject();

	if (OverlappedParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlappedParticle, GetActorLocation(), FRotator(0.0f), true);

	}

	if (OverlappedSound)
	{
		UGameplayStatics::PlaySound2D(this, OverlappedSound);
	}
	Destroy();

}


void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!bShouldUseOnOverlap)
	{
		return;
	}

	UseObject();
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


}

