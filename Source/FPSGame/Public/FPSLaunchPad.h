// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlaneComp;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ParticleSystem;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

private:
	UPROPERTY(EditAnywhere, Category = "Launch Pad | Character", DisplayName = "Character Launch Amount")
	float LaunchAmountForCharacter = 1500.f;

	UPROPERTY(EditAnywhere, Category = "Launch Pad | Character", DisplayName = "Launch Angle")
	float LaunchAngle = 45.f;
		//float ZLaunchCharacter = 1500.f;

	UPROPERTY(EditAnywhere, Category = "Launch Pad | Static Mesh Actor", DisplayName = "Static Mesh Actor Launch Amount")
	float LaunchAmountStaticMeshActor = 750.f;

	UPROPERTY(EditAnywhere, Category = "Launch Pad | Static Mesh Actor", DisplayName = "Z Launch Mesh Actor")
	float ZLaunchStaticMeshActor = 1250.f;
};
