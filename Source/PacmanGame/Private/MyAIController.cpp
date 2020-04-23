// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "NavigationData.h"

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActive)
		return;

	Super::Tick(DeltaTime);

	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (Player)
	{
		auto PlayerLocation = Player->GetActorLocation();
		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, GetPawn()->GetActorLocation(), PlayerLocation, ECollisionChannel::ECC_Visibility))
		{
			if (HitResult.GetActor()->GetFName() == Player->GetFName())
			{
				MoveToLocation(PlayerLocation, AcceptanceRadius);
			}
		}
	}
}