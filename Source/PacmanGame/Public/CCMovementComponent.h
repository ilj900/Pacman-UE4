// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "CCMovementComponent.generated.h"

class UCameraComponent;

/**
 * 
 */
UCLASS()
class PACMANGAME_API UCCMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	void Initialize(UStaticMeshComponent* MeshIn, UCameraComponent* CameraIn);
	void MoveForward(float Scale);
	void MoveRight(float Scale);

private:
	UStaticMeshComponent* Mesh;
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	float TorqueToAdd = 300000.f;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
