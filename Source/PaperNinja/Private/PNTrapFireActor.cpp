// Fill out your copyright notice in the Description page of Project Settings.


#include "PNTrapFireActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APNTrapFireActor::APNTrapFireActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticleSystemComp = CreateDefaultSubobject <UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComp->SecondsBeforeInactive = 1.0f;
	ConstructorHelpers::FObjectFinder<UParticleSystem> PSFinder(TEXT("ParticleSystem'/Game/Particles/PS_Fire.PS_Fire'"));
	if (PSFinder.Succeeded())
		ParticleSystemComp->SetTemplate(PSFinder.Object);
	RootComponent = ParticleSystemComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(ParticleSystemComp);
	BoxComp->SetRelativeLocation(FVector(0.0, 0.0, 35.0));
}

// Called when the game starts or when spawned
void APNTrapFireActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNTrapFireActor::OnOverlap);
}

// Called every frame
void APNTrapFireActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APNTrapFireActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(OtherActor, 100.0f, NULL, this, UDamageType::StaticClass());
}
