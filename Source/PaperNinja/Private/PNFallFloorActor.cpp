// Fill out your copyright notice in the Description page of Project Settings.


#include "PNFallFloorActor.h"

// Sets default values
APNFallFloorActor::APNFallFloorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/Architecture/SM_IronFloor.SM_IronFloor'"));
	if (MeshFinder.Succeeded())
		StaticMeshComp->SetStaticMesh(MeshFinder.Object);
	RootComponent = StaticMeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetRelativeLocation(FVector(0.0, 0.0, 10.0));
	BoxComp->SetBoxExtent(FVector(32.0, 32.0, 10));
}

// Called when the game starts or when spawned
void APNFallFloorActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNFallFloorActor::OnOverlap);
}

// Called every frame
void APNFallFloorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APNFallFloorActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FTimerDelegate SetSimulatePhysics;
	SetSimulatePhysics.BindLambda(
		[this]()
		{
			StaticMeshComp->SetSimulatePhysics(true);
		}
	);
	GetWorldTimerManager().SetTimer(TimerHandle, SetSimulatePhysics, 1.0f, false);
}