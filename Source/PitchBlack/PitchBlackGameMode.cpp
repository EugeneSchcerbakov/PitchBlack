// Fill out your copyright notice in the Description page of Project Settings.

#include "PitchBlack.h"
#include "PitchBlackGameMode.h"

APitchBlackGameMode::APitchBlackGameMode() : Super()
{
    const TCHAR* DefaultPawnFilename = TEXT("/Game/Blueprints/BP_PitchBlackCharacter");

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(DefaultPawnFilename);

    DefaultPawnClass = PlayerPawnFinder.Class;

    SVManager = new SonarVisionManager(GetWorld());
    SVManager->Init();
}

APitchBlackGameMode::~APitchBlackGameMode()
{
    delete SVManager;
}

void APitchBlackGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void APitchBlackGameMode::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    SVManager->Activate();
}

void APitchBlackGameMode::Tick(float DeltaTime)
{
    SVManager->Update(DeltaTime);
}
