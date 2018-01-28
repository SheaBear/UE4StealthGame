// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIPatrolGuard.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"

AFPSAIPatrolGuard::AFPSAIPatrolGuard()
{
	//UCapsuleComponent* TheCapsuleComponent = GetCapsuleComponent();
	//TheCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSAIPatrolGuard::OnCapsuleOverlap);
	//TheCapsuleComponent->bGenerateOverlapEvents = true;
}

void AFPSAIPatrolGuard::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* TheCapsuleComponent = GetCapsuleComponent();
	TheCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSAIPatrolGuard::OnCapsuleOverlap);
	TheCapsuleComponent->bGenerateOverlapEvents = true;
	//CurrentLocation = GetActorLocation();
	AAIController* TheAIController = Cast<AAIController>(GetController());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PatrolTargets, ThePatrolTargets);
	if (ThePatrolTargets.Num() > 0)
	{
		TheTarget = ThePatrolTargets[0];
		if (TheAIController)
		{
			TheAIController->MoveToActor(TheTarget);
			
		}
		
	}
}

void AFPSAIPatrolGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIPatrolGuard::OnHearingNoise(APawn* HeardPawn, const FVector& Location, float Volume)
{
	Super::OnHearingNoise(HeardPawn, Location, Volume);
	AAIController* TheAIController = Cast<AAIController>(GetController());
	if (TheAIController)
	{
		TheAIController->StopMovement();
		//UWorld* TheWorld = GetWorld();
		if (GetWorld())
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPSAIPatrolGuard::ResumeMovement, 3.0f, false);
		}
	}
}

void AFPSAIPatrolGuard::OnCapsuleOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, 
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	for(AActor* ThePatrolTarget : ThePatrolTargets)
	{
		if (ThePatrolTarget != OtherActor)
		{
			TheTarget = ThePatrolTarget;
			AAIController* TheAIController = Cast<AAIController>(GetController());
			if (TheAIController)
			{
				TheAIController->MoveToActor(TheTarget);
			}
		}
	}
}

void AFPSAIPatrolGuard::ResumeMovement()
{
	AAIController* TheAIController = Cast<AAIController>(GetController());
	if (TheAIController)
	{
		TheAIController->MoveToActor(TheTarget);
	}
}


