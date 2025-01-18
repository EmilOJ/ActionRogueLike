// Fill out your copyright notice in the Description page of Project Settings.


#include "TaMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATaMagicProjectile::ATaMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	// Collision settings
	Sphere->SetCollisionProfileName(TEXT("Projectile"));
    SetRootComponent(Sphere);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleEffect"));
	Particle->SetupAttachment(Sphere);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000.0f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bInitialVelocityInLocalSpace = true;
}


// Called when the game starts or when spawned
void ATaMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ATaMagicProjectile::OnHit);
}

void ATaMagicProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
	const FHitResult& Hit)
{
	// Destroy
	Destroy();
}

// Called every frame
void ATaMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

