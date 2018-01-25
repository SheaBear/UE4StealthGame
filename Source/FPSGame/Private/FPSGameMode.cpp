// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}


void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
		OnMissionCompleted(InstigatorPawn, bMissionSuccess);
		if (SpectatingViewpointClass)
		{
			APlayerController* ThePlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
			TArray <AActor*> TheActorArray;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, TheActorArray);
			if (TheActorArray.Num() > 0)
			{
				AActor* NewViewTarget = TheActorArray[0];
				ThePlayerController->SetViewTargetWithBlend(NewViewTarget, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
	}
}
