// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "GameFramework/GameModeBase.h"
#include "PacmanGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGAME_API APacmanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APacmanGameMode();
	virtual void BeginPlay() override;
	void ReducePickups();

private:
	int32_t PickupsRemain = 0;

	
};
