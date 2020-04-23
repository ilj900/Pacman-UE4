// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "NavigationSystem.h"

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActive)
		return;

	Super::Tick(DeltaTime);

	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto LocalPawn = GetPawn();
	FVector Location;
	if (Player)
	{
		Location = Player->GetActorLocation();
	}
	else
	{
		Location = LocalPawn->GetActorLocation();
	}

	if (Player)
	{
		auto PlayerLocation = Player->GetActorLocation();
		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, GetPawn()->GetActorLocation(), PlayerLocation, ECollisionChannel::ECC_Visibility))
		{
			if (HitResult.GetActor()->GetFName() == Player->GetFName())
			{
				UE_LOG(LogTemp, Warning, TEXT("Gimme some HUGS!"));
				MoveToLocation(PlayerLocation, AcceptanceRadius);
			}
		}
	}
	if (GetMoveStatus() == EPathFollowingStatus::Idle)
	{

		auto NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavSys)
		{
			FNavLocation Result;
			if (NavSys->GetRandomReachablePointInRadius(LocalPawn->GetActorLocation(), 2100.f, Result))
			{
				UE_LOG(LogTemp, Warning, TEXT("Searching begins"));
				MoveToLocation(Result.Location, AcceptanceRadius);
			}
		}
	}
}