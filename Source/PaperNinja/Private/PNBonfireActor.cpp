// Fill out your copyright notice in the Description page of Project Settings.


#include "PNBonfireActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
APNBonfireActor::APNBonfireActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/Props/SM_Bonfire.SM_Bonfire'"));
	if (MeshFinder.Succeeded())
		MeshComp->SetStaticMesh(MeshFinder.Object);
	RootComponent = MeshComp;

	FireFXComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireFX"));
	FireFXComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UParticleSystem> PSFinder(TEXT("ParticleSystem'/Game/Particles/PS_Fire.PS_Fire'"));
	if (PSFinder.Succeeded())
		FireFXComp->SetTemplate(PSFinder.Object);
	FireFXComp->SetRelativeLocation(FVector(0.0, 0.0, 130.0));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->SetRelativeLocation(FVector(0.0, 0.0, 210.0));
	PointLight->SetLightColor(FLinearColor(1.0f, 0.48f, 0.32f));
	PointLight->SetIntensity(500.0f);
	PointLight->SetAttenuationRadius(500.0f);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->SetRelativeLocation(FVector(0.0, 0.0, 130.0));
	ConstructorHelpers::FObjectFinder<USoundBase> SoundFinder(TEXT("ParticleSystem'/Game/Particles/PS_Fire.PS_Fire'"));
	if (SoundFinder.Succeeded())
		AudioComp->SetSound(SoundFinder.Object);

	ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenuationFinder(TEXT("SoundAttenuation'/Game/Audio/PN_AT_Default.PN_AT_Default'"));
	if (AttenuationFinder.Succeeded())
		AudioComp->AttenuationSettings = AttenuationFinder.Object;
}

// Called when the game starts or when spawned
void APNBonfireActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APNBonfireActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

