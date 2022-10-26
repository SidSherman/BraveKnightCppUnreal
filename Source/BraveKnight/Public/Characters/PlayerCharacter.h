// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};


UCLASS()
class BRAVEKNIGHT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/* 
	* Components
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera; // class means that we have not to add include in header file

	FORCEINLINE UCameraComponent* GetCameraComponent() { return FollowCamera; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* camera) { FollowCamera = camera; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm; // class means that we have not to add include in header file

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* springArm) { SpringArm = springArm; }


	/* 
	* Camera Settings
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;
	

	/*
	* Character's Attributes
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAttributes | Health")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterAttributes | Stamina")
		float MaxStamina;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintingSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunningSpeed;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	/*
	* Character's Attributes
	*/

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		FTimerHandle SprintHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes | Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes | Stamina")
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes | Stamina")
		float StaminaDecreaseDelta;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes | Stamina")
		float StaminaIncreaseDelta;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterAttributes | Stamina")
		float StaminaDeltaTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void SetMovementStatus(EMovementStatus Status);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetHealthPercent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetStaminaPercent();

	UFUNCTION()
		void IncreaseStamina();
	UFUNCTION()
		void DecreaseStamina();

	UFUNCTION()
		void SetHealth(float delta);





		
	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveRight(float value);

		void LookUp(float AxisValue);

		void Turn(float AxisValue);



	/*
	* @param rate is normalized rate
	*/
	UFUNCTION()
		void TurnAtRate(float Rate);
	UFUNCTION()
		void LookUpAtRate(float Rate);

	UFUNCTION()
		void StartSprint();
	UFUNCTION()
		void StopSprint();





};
