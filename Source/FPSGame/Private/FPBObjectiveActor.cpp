// Fill out your copyright notice in the Description page of Project Settings.


#include "FPBObjectiveActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPBObjectiveActor::AFPBObjectiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);


}

// Called when the game starts or when spawned
void AFPBObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPBObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPBObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, TheParticleSystem, GetActorLocation());
}

void AFPBObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//PlayEffects();
	//Make sure it was a character that overlapped.
	AFPSCharacter* TheFPSCharacter = Cast<AFPSCharacter>(OtherActor);
	if (TheFPSCharacter)
	{
		TheFPSCharacter->bIsCarryingObjective = true;
		PlayEffects();
		Destroy();
	}
}
