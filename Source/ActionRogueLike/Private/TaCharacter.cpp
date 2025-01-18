// Fill out your copyright notice in the Description page of Project Settings.


#include "TaCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATaCharacter::ATaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ATaCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void ATaCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();

	const FRotator ControlRotation = GetControlRotation();
	AddMovementInput(ControlRotation.Vector(), MoveVector.X);

	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, MoveVector.Y);
}

void ATaCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

// Called every frame
void ATaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATaCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATaCharacter::Look);
	}

}

