// Fill out your copyright notice in the Description page of Project Settings.

#include "SightAIController.h"
#include "Engine/Engine.h"

ASightAIController::ASightAIController() {

	auto config = NewObject<UAISenseConfig_Sight>();
	//Configuring the Sight Sense
	config->SightRadius = 600;
	config->LoseSightRadius = 700;
	config->DetectionByAffiliation.bDetectEnemies = true;
	config->DetectionByAffiliation.bDetectNeutrals = true;
	config->DetectionByAffiliation.bDetectFriendlies = true;

	if (!PerceptionComponent) {
		PerceptionComponent =
			CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightPerceptionComponent"));
	}

	PerceptionComponent->ConfigureSense(*config);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASightAIController::OnTargetPerceptionUpdate);

}

void ASightAIController::OnTargetPerceptionUpdate(AActor* Actor,
	FAIStimulus Stimulus) {
	//Retrieving Perceived Actors
	TArray<AActor*> PerceivedActors;
	
	PerceptionComponent->GetCurrentlyPerceivedActors(TSubclassOf<UAISense_Sight>(), PerceivedActors);
	//Calculating the Number of Perceived Actors and if the current target
	//Left or Entered the field of view.
	bool isEntered = PerceivedActors.Contains(Actor);
	int NumberObjectSeen = PerceivedActors.Num();
	
	//Formatting the string and printing it
	FString text = FString(Actor->GetName() + " has just " + (isEntered ?
		"Entered" : "Left") + " the field of view. Now " +
		FString::FromInt(NumberObjectSeen) + " objects are visible.");
	
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Turquoise, text);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}

