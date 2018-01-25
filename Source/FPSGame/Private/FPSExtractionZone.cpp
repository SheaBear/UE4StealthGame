// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapZone"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::OnOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	DecalComp->DecalSize = FVector(200.f, 200.f, 200.f);
	DecalComp->SetupAttachment(RootComponent);
}


void AFPSExtractionZone::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* TheFPSCharacter = Cast<AFPSCharacter>(OtherActor);
	if (TheFPSCharacter)
	{
		if (TheFPSCharacter->bIsCarryingObjective)
		{
			AFPSGameMode* TheGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (TheGameMode)
			{
				TheGameMode->CompleteMission(TheFPSCharacter, true);
			}
		}
		else
		{
			UGameplayStatics::PlaySound2D(this, TheSound);
			AFPSGameMode* TheGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (TheGameMode)
			{
				TheGameMode->OverlapExtractionNoItem(TheFPSCharacter);
			}
		}
	}
}
