// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControllableCharacter.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PACMANGAME_API AControllableCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AControllableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Gimball;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	FVector2D CameraInput;

	// Control functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PitchCamera(float Value);
	void YawCamera(float Value);

	float MaxVelocity = 10000.f;
};
