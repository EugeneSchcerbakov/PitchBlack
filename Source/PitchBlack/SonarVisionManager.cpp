// Fill out your copyright notice in the Description page of Project Settings.

#include "PitchBlack.h"
#include "SonarVisionManager.h"
#include "PitchBlackGameMode.h"

#include "Kismet/KismetMaterialLibrary.h"

SonarVisionManager::SonarVisionManager(UWorld* WorldPtr)
{
    World = WorldPtr;
}

SonarVisionManager::~SonarVisionManager()
{
}

void SonarVisionManager::Init()
{
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("/Game/Materials/M_SonarVision"));

    if (MaterialFinder.Succeeded())
    {
        MSonarVision = MaterialFinder.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> ParamFinder(TEXT("/Game/Materials/SonarVisionParam"));

    if (ParamFinder.Succeeded())
    {
        MParams = ParamFinder.Object;
    }
}

void SonarVisionManager::Activate()
{
    AGameMode* const GameMode = World->GetAuthGameMode();
    APitchBlackGameMode* PitchBlackGameMode = Cast<APitchBlackGameMode>(GameMode);

    MIDSonarVision = UMaterialInstanceDynamic::Create(MSonarVision, PitchBlackGameMode);

    for (TActorIterator<APostProcessVolume> ActorIter(World); ActorIter; ++ActorIter)
    {
        ActorIter->bEnabled = 1;
        ActorIter->AddOrUpdateBlendable(MIDSonarVision);
    }
}

void SonarVisionManager::Update(float DeltaTime)
{
    for (auto Iter = ActiveSources.begin(); Iter != ActiveSources.end();)
    {
        NoiseInfo& Info = (*Iter);

        Info.Time += DeltaTime;

        if (Info.Time * 0.3 < 1.0f) // 0.3 this is Rate
        {
            UKismetMaterialLibrary::SetScalarParameterValue(World, MParams, "Time_0", Info.Time);
            UKismetMaterialLibrary::SetScalarParameterValue(World, MParams, "Radius_0", Info.Radius);
            UKismetMaterialLibrary::SetVectorParameterValue(World, MParams, "Location_0", Info.WorldLocation);

            Iter++;
        }
        else
        {
            Iter = ActiveSources.erase(Iter);
        }
    }
}

void SonarVisionManager::AddSource(const NoiseInfo &Info)
{
    ActiveSources.push_back(Info);
}
