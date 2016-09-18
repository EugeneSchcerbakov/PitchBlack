// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
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

    void BeginPlay() override;
    void PostInitializeComponents() override;

	void UpdateSonarVisionPProcFX();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Sonar Vision")
    class UMaterialInstanceDynamic* MIDSonarVision;

	UPROPERTY(BlueprintReadOnly, Category = "Sonar Vision")
	class UMaterial* MSonarVision;

private:
	void InitSonarVision();
};
