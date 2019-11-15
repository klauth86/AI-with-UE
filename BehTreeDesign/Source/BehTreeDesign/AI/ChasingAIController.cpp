// Fill out your copyright notice in the Description page of Project Settings.

#include "ChasingAIController.h"
#include "BehTreeDesignCharacter.h"

AChasingAIController::AChasingAIController() {
	SightConfig = NewObject<UAISenseConfig_Sight>();
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	if (!PerceptionComponent) {
		PerceptionComponent =
			CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightPerceptionComponent"));
	}

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AChasingAIController::OnTargetPerceptionUpdate);
}


void AChasingAIController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus) {
	if (Cast<ABehTreeDesignCharacter>(Actor)) {
		LastKnownPlayerPosition = Stimulus.StimulusLocation;
		bCanSeePlayer = Stimulus.WasSuccessfullySensed();
	}
}
