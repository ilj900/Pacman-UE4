// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (Player)
	{
		LocationOfInterest = Player->GetActorLocation();
	}
	else
	{
		//TODO generate location to reach
	}


	MoveToLocation(LocationOfInterest, AcceptanceRadius);
}