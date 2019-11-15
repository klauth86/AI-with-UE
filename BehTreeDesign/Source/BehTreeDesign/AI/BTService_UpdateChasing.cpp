// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_UpdateChasing.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ChasingAIController.h"

UBTService_UpdateChasing::UBTService_UpdateChasing(const
	FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_UpdateChasing::OnBecomeRelevant(UBehaviorTreeComponent &
	OwnerComp, uint8 * NodeMemory) {
	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComp == NULL) {
		return;
	}

	if (PlayerKey.IsSet())
		return;

	//Retrieve Player and Update the Blackboard
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
	if (FoundActors[0]) {
		BlackboardComp->SetValueAsObject(PlayerKey.SelectedKeyName,	FoundActors[0]);
	}
}

void UBTService_UpdateChasing::TickNode(UBehaviorTreeComponent & OwnerComp,
	uint8 * NodeMemory, float DeltaSeconds) {
	//Get Blackboard Component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == NULL) {
		return;
	}

	//Get AI Controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) {
		return;
	}

	AChasingAIController* ChasingController =
	Cast<AChasingAIController>(AIController);
	if (!ChasingController) {
		return;
	}

	BlackboardComp->SetValueAsBool(CanSeePlayerKey.SelectedKeyName,
		ChasingController->bCanSeePlayer);

	if (ChasingController->bCanSeePlayer != bLastCanSeePlayer) {
		BlackboardComp->SetValueAsVector(LastKnownPositionKey.SelectedKeyName,
			ChasingController->LastKnownPlayerPosition);
	}

	bLastCanSeePlayer = ChasingController->bCanSeePlayer;

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

FString UBTService_UpdateChasing::GetStaticDescription() const {
	return FString::Printf(TEXT("%s: '%s'"), TEXT("Player Class"),
		PlayerClass ? *PlayerClass->GetName() : TEXT(""))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("PlayerKey"),
			PlayerKey.IsSet() ? *PlayerKey.SelectedKeyName.ToString() : TEXT("")))
		.Append(FString::Printf(TEXT("\n%s: '%s'"),
			TEXT("LastKnownPositionKey"), LastKnownPositionKey.IsSet() ?
			*LastKnownPositionKey.SelectedKeyName.ToString() : TEXT("")))
		.Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("CanSeePlayerKey"),
			CanSeePlayerKey.IsSet() ? *CanSeePlayerKey.SelectedKeyName.ToString() :
			TEXT("")));
}