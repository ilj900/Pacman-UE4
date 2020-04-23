// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:

	void Tick(float DeltaTime);

	bool bIsActive = true;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 150.f;
	
};
