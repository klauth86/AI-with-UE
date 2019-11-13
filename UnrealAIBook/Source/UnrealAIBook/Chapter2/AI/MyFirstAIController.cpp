// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFirstAIController.h"
#include "UnrealAIBookCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

void AMyFirstAIController::Possess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	AUnrealAIBookCharacter* Character = Cast<AUnrealAIBookCharacter>(InPawn);
	if (Character != nullptr) {
		UBehaviorTree* BehaviorTree = Character->BehaviorTree;
		if (BehaviorTree != nullptr) {
			RunBehaviorTree(BehaviorTree);
		}
	}
}
