// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"


UCLASS()
class BRAVEKNIGHT_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPawn();

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* MeshComponent; // class means that we have not to add include in header file

	FORCEINLINE USkeletalMeshComponent* GetMeshComponent() { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(USkeletalMeshComponent* Mesh) { MeshComponent = Mesh; }


	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* CapsuleCollisionComponent; // class means that we have not to add include in header file

	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() { return CapsuleCollisionComponent; }
	FORCEINLINE void SetCapsuleComponent(UCapsuleComponent* Capsule) { CapsuleCollisionComponent = Capsule; }


	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera; // class means that we have not to add include in header file


	FORCEINLINE UCameraComponent* GetCameraComponent() { return Camera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* camera) { Camera = camera; }
	
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm; // class means that we have not to add include in header file

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* springArm) { SpringArm = springArm; }



	// movement parameters

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCustomPawnMovementComponent* MovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	/*
	FORCEINLINE UCustomPawnMovementComponent* GetMovementComponent() { return MovementComponent; }
	FORCEINLINE void SetMovementComponent(UCustomPawnMovementComponent* movementComponent) { MovementComponent = movementComponent; }
	*/

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MaxVelocity;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:


	UPROPERTY()
		FVector CurrentVelocity;

	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveRight(float value);

};
