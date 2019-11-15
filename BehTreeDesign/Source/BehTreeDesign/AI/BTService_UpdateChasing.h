// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehTreeDesignCharacter.h"
#include "BTService_UpdateChasing.generated.h"

/**
 * 
 */
UCLASS()
class BEHTREEDESIGN_API UBTService_UpdateChasing : public UBTService
{
	GENERATED_BODY()

	UBTService_UpdateChasing(const FObjectInitializer& ObjectInitializer =
		FObjectInitializer::Get());
public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector CanSeePlayerKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector PlayerKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector LastKnownPositionKey;

	UPROPERTY(EditAnywhere, Category = PlayerClass)
		TSubclassOf<ABehTreeDesignCharacter> PlayerClass;
private:
	bool bLastCanSeePlayer;
	
protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;
};
