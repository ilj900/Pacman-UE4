// Fill out your copyright notice in the Description page of Project Settings.


#include "CCMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

void UCCMovementComponent::Initialize(UStaticMeshComponent* MeshIn, UCameraComponent* CameraIn)
{
	Mesh = MeshIn;
	Camera = CameraIn;
}

void UCCMovementComponent::MoveForward(float Scale)
{
	if (Mesh && Camera)
	{
		auto CameraRight = Camera->GetRightVector();
		CameraRight.Z = 0.f;
		auto AngularVelocity = Mesh->GetPhysicsAngularVelocityInDegrees();
		Mesh->AddTorqueInRadians(CameraRight.GetSafeNormal() * TorqueToAdd * Scale);
	}
}

void UCCMovementComponent::MoveRight(float Scale)
{
	if (Mesh && Camera)
	{
		auto CameraFront = Camera->GetForwardVector();
		CameraFront.Z = 0.f;
		Mesh->AddTorqueInRadians(-CameraFront.GetSafeNormal() * TorqueToAdd * Scale);
	}
}

void UCCMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto ForwardVector = Camera->GetForwardVector();
	ForwardVector.Z = 0.f;
	ForwardVector.Normalize();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardIntention = FVector::DotProduct(ForwardVector, AIForwardIntention);
	auto RightIntention = FVector::CrossProduct(ForwardVector, AIForwardIntention).Z;

	if (bForceMaxSpeed)
	{
		ForwardIntention *= MoveVelocity.Size();
		RightIntention *= MoveVelocity.Size();
	}


	MoveForward(ForwardIntention);
	MoveRight(RightIntention);
}
