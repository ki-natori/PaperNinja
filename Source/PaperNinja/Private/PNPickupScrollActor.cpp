// Fill out your copyright notice in the Description page of Project Settings.


#include "PNPickupScrollActor.h"
#include "PNPlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APNPickupScrollActor::APNPickupScrollActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/Props/SM_Scroll.SM_Scroll'"));
	if (MeshFinder.Succeeded())
		StaticMeshComp->SetStaticMesh(MeshFinder.Object);
	StaticMeshComp->SetMobility(EComponentMobility::Movable);
	StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, 28.0));
	StaticMeshComp->SetRelativeRotation(FRotator(-40.0, 0.0, 0.0));
	StaticMeshComp->SetupAttachment(SceneComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("Pickup"));

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(SceneComp);
	BoxComp->SetRelativeLocation(FVector(0.0, 0.0, 28.0));
	BoxComp->SetBoxExtent(FVector(28.0, 28.0, 28.0));

	FXComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FX"));
	FXComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UParticleSystem> PSFinder(TEXT("ParticleSystem'/Game/Particles/PS_GoalItem.PS_GoalItem'"));
	if (PSFinder.Succeeded())
		FXComp->SetTemplate(PSFinder.Object);
}

// Called when the game starts or when spawned
void APNPickupScrollActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNPickupScrollActor::OnOverlap);
}

// Called every frame
void APNPickupScrollActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APNPickupScrollActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APNPlayerPawn* PlayerPawn = Cast<APNPlayerPawn>(OtherActor);
	if (PlayerPawn)
	{
		PlayerPawn->ObtainScroll();
		Destroy();
	}
}