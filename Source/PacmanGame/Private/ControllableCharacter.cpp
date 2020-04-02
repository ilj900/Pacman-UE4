// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AControllableCharacter::AControllableCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, CameraSpringArm->SocketName);

}

// Called when the game starts or when spawned
void AControllableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControllableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += RotationInput.X;
		SetActorRotation(NewRotation);
	}

	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + RotationInput.Y, -80.0f, -15.0f);
		CameraSpringArm->SetWorldRotation(NewRotation);
	}

	{
		if (!MovementInput.IsZero())
		{
			MovementInput = MovementInput.GetSafeNormal() * 1000.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void AControllableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AControllableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AControllableCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AControllableCharacter::YawCamera);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AControllableCharacter::PitchCamera);
}

void AControllableCharacter::MoveForward(float Value)
{
	MovementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AControllableCharacter::MoveRight(float Value)
{
	MovementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AControllableCharacter::PitchCamera(float Value)
{
	RotationInput.Y = Value;
}

void AControllableCharacter::YawCamera(float Value)
{
	RotationInput.X = Value;
}


