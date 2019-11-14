// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvQueryContext_Player.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance&
	QueryInstance, FEnvQueryContextData& ContextData) const {
	if (auto world = GetWorld()) {
		if (auto controller = world->GetFirstPlayerController()) {
			if (auto pawn = controller->GetPawn()) {
				UEnvQueryItemType_Actor::SetContextHelper(ContextData, pawn);
			}
		}
	}
}


