// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Mode")
	void OverlapExtractionNoItem(APawn* InstigatorPawn);
	
	UPROPERTY(EditDefaultsOnly, Category = "End Game Camera")
	TSubclassOf<AActor> SpectatingViewpointClass;
};



