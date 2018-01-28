// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSAIGuard.h"
#include "GuardPatrolZone.h"
#include "FPSAIPatrolGuard.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSAIPatrolGuard : public AFPSAIGuard
{
	GENERATED_BODY()
	
public:

	AFPSAIPatrolGuard();

	UPROPERTY(EditDefaultsOnly, Category = "AI | Targets")
	TSubclassOf<AActor> PatrolTargets;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UFUNCTION()
	virtual void OnHearingNoise(APawn* HeardPawn, const FVector& Location, float Volume) override;

	UFUNCTION()
	void ResumeMovement();

	/*UPROPERTY()
	FVector CurrentLocation;*/

	UPROPERTY()
	TArray<AActor*> ThePatrolTargets;
	
	UPROPERTY()
	AActor* TheTarget;
};
