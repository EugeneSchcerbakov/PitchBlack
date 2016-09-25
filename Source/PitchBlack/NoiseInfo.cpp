// Fill out your copyright notice in the Description page of Project Settings.

#include "PitchBlack.h"
#include "NoiseInfo.h"

NoiseInfo::NoiseInfo(const FVector& L, float R)
{
    WorldLocation = L;
    Radius = R;
    Time = 0.0f;
}
