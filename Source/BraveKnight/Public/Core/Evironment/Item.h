// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Evironment/UsebleObject.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class BRAVEKNIGHT_API AItem : public AUsebleObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		bool bShouldUseOnOverlap;

	FORCEINLINE bool GetShouldUseOnOverlap() { return bShouldUseOnOverlap; }

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class USphereComponent* SphereCollision;

	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereCollision; }
	FORCEINLINE void SetSphereComponent(USphereComponent* Sphere) { SphereCollision = Sphere; }

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UParticleSystemComponent* IdleParticle;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class UParticleSystem* OverlappedParticle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		class USoundCue* OverlappedSound;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseObject() override;
	

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
