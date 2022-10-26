// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingPlatform.generated.h"

UCLASS(BlueprintType)
class BRAVEKNIGHT_API AFlyingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyingPlatform();

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

	//TargetPoints
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Flying Parameters")
		TArray<AActor*> FlyingPoints;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Flying Parameters")
		float LocationTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Parameters")
	float FlyingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flying Parameters")
		bool bShouldInterp;

	//Should platform move or not
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Flying Parameters")
		bool bShouldFly;

	//Should platform move betwee points reapeatly or not
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Flying Parameters")
		bool bShouldRepeatEndlessly;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flying Parameters")
		float PauseTime;

	FTimerHandle PauseTimer;

	bool bSwitchToggle;

	

protected:
	// Called when the game starts or when spawnedц
	virtual void BeginPlay() override;

	UPROPERTY()
		int CurrentPointIndex;
	UPROPERTY()
		AActor* CurrentPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//TargetPointsSelector
	UFUNCTION()
		void PointSelector(int NewIndex);
	UFUNCTION()
		void PointSelectorToggle();

};
