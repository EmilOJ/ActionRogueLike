// Fill out your copyright notice in the Description page of Project Settings.


#include "TaExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ATaExplosiveBarrel::ATaExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void ATaExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentHit.AddDynamic(this, &ATaExplosiveBarrel::HitCallbackFunc);
}

void ATaExplosiveBarrel::HitCallbackFunc(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit!"));
	RadialForceComp->FireImpulse();
}

// Called every frame
void ATaExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

