// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskNode_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/Navigation/NavigationSystem.h"

EBTNodeResult::Type UBTTaskNode_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) {
	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL) {
		return EBTNodeResult::Failed;
	}

	//Get Controlled Pawn
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn) {
		return EBTNodeResult::Failed;
	}

	//Get Navigation System
	UNavigationSystem* NavSys = GetWorld()->GetNavigationSystem();
	if (!NavSys) {
		return EBTNodeResult::Failed;
	}

	//Prepare variables for Query
	FNavLocation Result;
	FVector Origin = ControlledPawn->GetActorLocation();

	if (NavSys->GetRandomReachablePointInRadius(Origin, Radius, Result)) {
		BlackboardComp->SetValueAsVector(RandomDestination.SelectedKeyName,
			Result.Location);
	}
	else {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}

FString UBTTaskNode_FindRandomLocation::GetStaticDescription() const {
	return FString::Printf(TEXT("%s: '%s'"), TEXT("DestinationKey"),
		RandomDestination.IsSet() ? *RandomDestination.SelectedKeyName.ToString() :
		TEXT(""))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("Radius"),
			*FString::SanitizeFloat(Radius)));
}

