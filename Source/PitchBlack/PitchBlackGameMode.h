// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SonarVisionManager.h"

#include "PitchBlackGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PITCHBLACK_API APitchBlackGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	APitchBlackGameMode();
    ~APitchBlackGameMode();

    void BeginPlay() override;
    void PostInitializeComponents() override;
    void Tick(float DeltaTime) override;

	inline SonarVisionManager* GetSonarVisionManager() {return SVManager;};

protected:
    SonarVisionManager* SVManager;
};
