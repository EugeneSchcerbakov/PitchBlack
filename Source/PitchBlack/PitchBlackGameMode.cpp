// Fill out your copyright notice in the Description page of Project Settings.

#include "PitchBlack.h"
#include "PitchBlackGameMode.h"

#include "Kismet/GameplayStatics.h"

APitchBlackGameMode::APitchBlackGameMode() : Super()
{
    const TCHAR* DefaultPawnFilename = TEXT("/Game/Blueprints/BP_PitchBlackCharacter");

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(DefaultPawnFilename);

    DefaultPawnClass = PlayerPawnFinder.Class;

    InitSonarVision();
}

void APitchBlackGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void APitchBlackGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    UpdateSonarVisionPProcFX();
}

void APitchBlackGameMode::UpdateSonarVisionPProcFX()
{
    // Create dynamic material instance from specified material

    MIDSonarVision = UMaterialInstanceDynamic::Create(MSonarVision, this);

    for (TActorIterator<APostProcessVolume> ActorIter(GetWorld()); ActorIter; ++ActorIter)
    {
        ActorIter->bEnabled = 1;
        ActorIter->AddOrUpdateBlendable(MIDSonarVision);
    }
}

void APitchBlackGameMode::InitSonarVision()
{
    // Find shader material and create reference to it

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("/Game/Materials/M_SonarVision"));

    if (MaterialFinder.Succeeded())
    {
        MSonarVision = MaterialFinder.Object;
    }
}
