// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TestPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pawns/CustomPawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATestPawn::ATestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create root component
	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	//Create and attach Mesh and Camera to Root
	CapsuleCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleCollisionComponent->SetupAttachment(GetRootComponent());
	CapsuleCollisionComponent->SetCollisionProfileName(TEXT("Pawn"));
	SetRootComponent(CapsuleCollisionComponent);


	//Create Spring arm and camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(GetSpringArmComponent());



	//Create and attach Mesh and Camera to Root
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetCapsuleComponent());

	/*
	* Set assets parameters throught code
	* I think that this is the wrong way cause it is not flexbible 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		MeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));

	}
	*/

	//Create MovemetComponent and set Component that will be moved by MovementComponent 
	MovementComponent = CreateDefaultSubobject<UCustomPawnMovementComponent>(TEXT("PawnMovementComponent"));
	MovementComponent->UpdatedComponent = GetRootComponent();

	// Set Velocity Parameters
	MaxVelocity = 10.0f;
	CurrentVelocity = FVector(0.0f);


	// AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* The way to move pawn throught set Location Directly
	*
	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);
	*/




}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATestPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATestPawn::MoveRight);
	
}


void ATestPawn::MoveForward(float value)
{	
	// The way to move pawn throught set Location Directly
	//CurrentVelocity.X = - FMath::Clamp(value, -1.0, 1.0) * MaxVelocity;


	FVector ForwardDirection = GetActorForwardVector();

	if (MovementComponent)
	{
		MovementComponent->AddInputVector(ForwardDirection * value * MaxVelocity);
	}
	else
	{
		AddMovementInput(ForwardDirection, value * MaxVelocity);
	}
}

void ATestPawn::MoveRight(float value)
{
	// The way to move pawn throught set Location Directly
	//CurrentVelocity.Y = - FMath::Clamp(value, -1.0, 1.0) * MaxVelocity;

	FVector RightDirection = GetActorRightVector();
	

	if (MovementComponent)
	{
		MovementComponent->AddInputVector(RightDirection * value * MaxVelocity);
	}
	else
	{
		AddMovementInput(RightDirection, value * MaxVelocity);
	}

}

UPawnMovementComponent* ATestPawn::GetMovementComponent() const
{
	return MovementComponent;
}


