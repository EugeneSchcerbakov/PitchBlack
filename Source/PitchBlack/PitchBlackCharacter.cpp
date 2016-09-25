// Fill out your copyright notice in the Description page of Project Settings.

#include "PitchBlack.h"
#include "PitchBlackCharacter.h"
#include "SonarVisionManager.h"

#include "PitchBlackGameMode.h"

// Sets default values
APitchBlackCharacter::APitchBlackCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize(55.0f, 187.0f / 2.0f);

    BaseTurnRate = 45.0f;
    BaseLookUpRate = 45.0f;

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->RelativeLocation = FVector(-39.0f, 1.75f, 64.0f);
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APitchBlackCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APitchBlackCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APitchBlackCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

//    InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
//    InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    InputComponent->BindAction("Noise", IE_Pressed, this, &APitchBlackCharacter::MakeNoise);

    InputComponent->BindAxis("MoveForward", this, &APitchBlackCharacter::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &APitchBlackCharacter::MoveRight);

    InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    InputComponent->BindAxis("TurnRate", this, &APitchBlackCharacter::TurnAtRate);
    InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    InputComponent->BindAxis("LookUpRate", this, &APitchBlackCharacter::LookUpAtRate);
}

void APitchBlackCharacter::MoveForward(float Val)
{
    if (Val != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Val);
    }
}

void APitchBlackCharacter::MoveRight(float Val)
{
    if (Val != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Val);
    }
}

void APitchBlackCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APitchBlackCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APitchBlackCharacter::MakeNoise()
{
    UWorld* const World = GetWorld();
    AGameMode* const GameMode = World->GetAuthGameMode();
    APitchBlackGameMode* PitchBlackGameMode = Cast<APitchBlackGameMode>(GameMode);

    if (PitchBlackGameMode)
    {
        FVector Position = GetFirstPersonCameraComponent()->GetComponentLocation();
        float Radius = 1.25f;

        SonarVisionManager* SVMgr = PitchBlackGameMode->GetSonarVisionManager();
        SVMgr->AddSource(NoiseInfo(Position, Radius));
    }
}