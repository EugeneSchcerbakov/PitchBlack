// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NoiseInfo.h"

#include <vector>

/**
 * 
 */
class PITCHBLACK_API SonarVisionManager
{
public:
    SonarVisionManager(class UWorld *WorldPtr);

    ~SonarVisionManager();

    void Init();
    void Activate();
    void Update(float DeltaTime);
    void AddSource(const NoiseInfo& Info);

protected:
    class UWorld *World;

    class UMaterialParameterCollection *MParams;

    class UMaterialInstanceDynamic *MIDSonarVision;

    class UMaterial *MSonarVision;

private:
    std::vector<NoiseInfo> ActiveSources;
};
