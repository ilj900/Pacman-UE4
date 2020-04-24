// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "ControllableCharacter.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collision Mesh"));
	if (BallMesh.Succeeded())
		CollisionMesh->SetStaticMesh(BallMesh.Object);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);
	CollisionMesh->SetSimulatePhysics(false);
	CollisionMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = CollisionMesh;

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Overlapper = Cast<AControllableCharacter>(OtherActor);
	if (Overlapper)
	{
		if (Overlapper->IsPlayerControlled())
		{
			UE_LOG(LogTemp, Warning, TEXT("Me, Overlap!"));
			SetLifeSpan(0.1f);
		}
	}
}

