// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "SightAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAIBOOK_API ASightAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASightAIController();
	
	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
};
