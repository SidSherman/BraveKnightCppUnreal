// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Spring arm and camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FollowCamera->SetupAttachment(GetSpringArmComponent(), USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true; // Rotate arm based on controller

	MaxHealth = 100;
	MaxStamina = 100;
	Stamina = 0;
	Health = 0;

	RunningSpeed = 1000;
	SprintingSpeed = 650;


	StaminaDecreaseDelta = 1;
	StaminaIncreaseDelta = 1;
	StaminaDeltaTime = 1;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;
	Health = MaxHealth;
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Checks that PlayerInputComponent is valid
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed,this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &APlayerCharacter::StopJumping);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("TurnAtRate"), this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookAtRate"), this, &APlayerCharacter::LookUpAtRate);
	
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerCharacter::StopSprint);

}

void APlayerCharacter::MoveForward(float value)
{

	if (Controller != nullptr && value != 0.0f)
	{

		const FRotator Rotation = Controller->GetControlRotation();

		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		//Get Forward Direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, value);
	}

}

void APlayerCharacter::MoveRight(float value)
{

	if (Controller != nullptr && value != 0.0f)
	{

		const FRotator Rotation = Controller->GetControlRotation();

		const FRotator YawRotation(0.f, Rotation.Yaw , 0.f);

		//Get Forward Direction
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}

}

void APlayerCharacter::Turn(float Value)
{

	

	AddControllerYawInput(Value);
	
}

void APlayerCharacter::LookUp(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Rotation to point is %f"), Value);
	AddControllerPitchInput(Value);
	
}



void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}


void APlayerCharacter::LookUpAtRate(float Rate)

{
	AddControllerPitchInput(Rate* BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


float APlayerCharacter::GetHealthPercent()
{
	return Health / MaxHealth;
}


float APlayerCharacter::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}


void APlayerCharacter::SetHealth(float delta)
{
	Health = FMath::Clamp(Health + delta, 0, MaxHealth);
}


void APlayerCharacter::IncreaseStamina()
{
	Stamina = FMath::Clamp(Stamina + StaminaIncreaseDelta, 0, MaxStamina);
	if (Stamina >= MaxStamina)
	{
		GetWorldTimerManager().ClearTimer(SprintHandle);
	}
}

void APlayerCharacter::DecreaseStamina()
{
	Stamina = FMath::Clamp(Stamina - StaminaDecreaseDelta, 0, MaxStamina);

	if (Stamina <= 0)
	{
		StopSprint();

	}
}



void APlayerCharacter::SetMovementStatus(EMovementStatus Status )
{
	MovementStatus = Status;
}

void APlayerCharacter::StartSprint()
{

	if (GetStaminaPercent() < 0.2) {
		return;
	}

	if (MovementStatus == EMovementStatus::EMS_Sprinting)
	{
		return;
	}

	if (GetWorldTimerManager().IsTimerActive(SprintHandle))
	{
		GetWorldTimerManager().ClearTimer(SprintHandle);
	}


	SetMovementStatus(EMovementStatus::EMS_Sprinting);

	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;

	GetWorldTimerManager().SetTimer(SprintHandle, this, &APlayerCharacter::DecreaseStamina, StaminaDeltaTime, true);
}



void APlayerCharacter::StopSprint()
{

	UE_LOG(LogTemp, Warning, TEXT("StopSprint"));

	if (MovementStatus == EMovementStatus::EMS_Normal)
	{
		return;
	}

	SetMovementStatus(EMovementStatus::EMS_Normal);

	GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;

	GetWorldTimerManager().ClearTimer(SprintHandle);

	

	GetWorldTimerManager().SetTimer(SprintHandle, this, &APlayerCharacter::IncreaseStamina, StaminaDeltaTime, true);
}

