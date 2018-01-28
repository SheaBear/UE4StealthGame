// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardPatrolZone.h"
#include "Components/BoxComponent.h"


// Sets default values
AGuardPatrolZone::AGuardPatrolZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGuardPatrolZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuardPatrolZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

