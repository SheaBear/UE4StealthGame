// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"



// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootSceneComponent = CreateDefaultSubobject <USceneComponent>(TEXT("Root Component"));
	RootComponent = RootSceneComponent;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Launchpad Base"));

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComp->SetBoxExtent(FVector(250.f));
	BoxComp->SetupAttachment(MeshComp);

	PlaneComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Plane"));
	PlaneComp->SetupAttachment(BoxComp);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnBoxOverlap);

}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSLaunchPad::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* TheFPSCharacter = Cast<AFPSCharacter>(OtherActor);
	if (TheFPSCharacter)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, GetActorLocation());
		FRotator LaunchPadRotation = GetActorRotation();
		LaunchPadRotation.Pitch += LaunchAngle;
		FVector LaunchVelocity = LaunchPadRotation.Vector() * LaunchAmountForCharacter;
		TheFPSCharacter->LaunchCharacter(LaunchVelocity, true, true);
		//FVector TheForwardVector = GetActorForwardVector();
		//TheFPSCharacter->LaunchCharacter(FVector(TheForwardVector.X * LaunchAmountForCharacter, TheForwardVector.Y * LaunchAmountForCharacter, ZLaunchCharacter),false, false);
	}
	//Was not a character.
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, GetActorLocation());
		AStaticMeshActor* TheStaticMeshActor = Cast<AStaticMeshActor>(OtherActor);
		if (TheStaticMeshActor)
		{
			FRotator LaunchPadRotation = GetActorRotation();
			LaunchPadRotation.Pitch += LaunchAngle;
			FVector LaunchVelocity = LaunchPadRotation.Vector() * LaunchAmountForCharacter;
			TheStaticMeshActor->GetStaticMeshComponent()->AddImpulse(LaunchVelocity, FName(NAME_None), true);
			//FVector TheForwardVector = GetActorForwardVector();
			//TheStaticMeshActor->GetStaticMeshComponent()->AddImpulse(FVector(TheForwardVector.X * LaunchAmountStaticMeshActor, TheForwardVector.Y * LaunchAmountStaticMeshActor, ZLaunchStaticMeshActor),
			//	FName(NAME_None), true);
		}
	}
}

