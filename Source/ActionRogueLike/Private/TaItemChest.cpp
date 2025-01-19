// Fill out your copyright notice in the Description page of Project Settings.


#include "TaItemChest.h"

// Sets default values
ATaItemChest::ATaItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    SetRootComponent(BodyMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BodyMesh);
}

void ATaItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	const FRotator OpenRotation = FRotator(50, 0, 0);
	LidMesh->SetRelativeRotation(OpenRotation);
}


// Called when the game starts or when spawned
void ATaItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

