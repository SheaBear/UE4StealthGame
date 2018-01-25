// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHoleActor.h"


// Sets default values
ABlackHoleActor::ABlackHoleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SuckingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SuckingSphere"));
	SuckingSphere->SetSphereRadius(20000.f);

	DestroyingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DestroyingSphere"));
	DestroyingSphere->SetSphereRadius(200.f);

	TheMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	DestroyingSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHoleActor::OnComponentOverlap);

}

// Called when the game starts or when spawned
void ABlackHoleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SuckingSphere->GetOverlappingComponents(TheComponentsToDestroy);
	for (UPrimitiveComponent* TheComponent : TheComponentsToDestroy)
	{
		TheComponent->AddRadialForce(GetActorLocation(), SuckingSphere->GetUnscaledSphereRadius(), -2000.f, ERadialImpulseFalloff::RIF_Constant, true);
	}
}


void ABlackHoleActor::OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}
