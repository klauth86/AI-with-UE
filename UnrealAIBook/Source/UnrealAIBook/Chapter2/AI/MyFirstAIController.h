// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyFirstAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAIBOOK_API AMyFirstAIController : public AAIController
{
	GENERATED_BODY()	
	
public:
	//** override the OnPossess function to run the behavior tree.
	void Possess(APawn* InPawn) override;	
};
