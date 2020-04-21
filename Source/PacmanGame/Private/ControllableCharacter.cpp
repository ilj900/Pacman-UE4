// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "CCMovementComponent.h"

// Sets default values
AControllableCharacter::AControllableCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	CollisionMesh->SetStaticMesh(BallMesh.Object);
	CollisionMesh->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	CollisionMesh->SetSimulatePhysics(true);
	CollisionMesh->SetAngularDamping(20.0f);
	CollisionMesh->SetLinearDamping(0.1f);
	CollisionMesh->BodyInstance.MassScale = 3.5;
	CollisionMesh->BodyInstance.MaxAngularVelocity = 50.f;
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetRelativeScale3D(FVector(0.43));
	RootComponent = CollisionMesh;

	Gimball = CreateDefaultSubobject<USceneComponent>(TEXT("Gimball"));
	Gimball->SetupAttachment(RootComponent);
	Gimball->SetUsingAbsoluteRotation(true);

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));

	CameraSpringArm->SetupAttachment(Gimball);
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	MovementComponent = CreateDefaultSubobject<UCCMovementComponent>(TEXT("Movement Component"));
	MovementComponent->Initialize(CollisionMesh, Camera);
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
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		CameraSpringArm->SetWorldRotation(NewRotation);
	}

}

// Called to bind functionality to input
void AControllableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (MovementComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UCCMovementComponent::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", MovementComponent, &UCCMovementComponent::MoveRight);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
	PlayerInputComponent->BindAxis("CameraYaw", this, &AControllableCharacter::YawCamera);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AControllableCharacter::PitchCamera);
}

void AControllableCharacter::PitchCamera(float Value)
{
	CameraSpringArm->AddLocalRotation(FRotator(Value, 0.f, 0.f));
}

void AControllableCharacter::YawCamera(float Value)
{
	Gimball->AddLocalRotation(FRotator(0.f, Value, 0.f));
}


