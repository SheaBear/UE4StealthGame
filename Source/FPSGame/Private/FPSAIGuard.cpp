// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMath.h"
#include "FPSGameMode.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnSeeingPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnHearingNoise);



}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFPSAIGuard::OnSeeingPawn(APawn* SeenPawn)
{
	if (SeenPawn)
	{
		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.f, 12, FColor::Blue, false, 10.f);
		AFPSGameMode* TheGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (TheGameMode)
		{
			TheGameMode->CompleteMission(SeenPawn, false);
		}
	}
}

void AFPSAIGuard::OnHearingNoise(APawn* HeardPawn, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Red, false, 10.f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;
	SetActorRotation(NewRotation);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPSAIGuard::ReturnToOriginalRotation, 5.0f);
}

void AFPSAIGuard::ReturnToOriginalRotation()
{
	SetActorRotation(OriginalRotation);
}


void AFPSAIGuard::SetGuardState(EAIState NewGuardState)
{
	if (GuardState != NewGuardState)
	{
		GuardState = NewGuardState;
		OnStateChanged(NewGuardState);
	}
}

