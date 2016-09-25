// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PitchBlack.h"

/**
 * 
 */
struct PITCHBLACK_API NoiseInfo
{
    NoiseInfo(const FVector& L, float R);

    FVector WorldLocation;
    float Radius;
    float Time;
};
