// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

APacmanGameMode::APacmanGameMode()
{

}

void APacmanGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickUp::StaticClass(), Result);
	UE_LOG(LogTemp, Warning, TEXT("Total number of pickups: %i"), Result.Num());
	PickupsRemain = Result.Num();
}

void APacmanGameMode::ReducePickups()
{
	UE_LOG(LogTemp, Warning, TEXT("Reducing"));
	--PickupsRemain;
	if (PickupsRemain == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("YOU WIN"));
	}
}