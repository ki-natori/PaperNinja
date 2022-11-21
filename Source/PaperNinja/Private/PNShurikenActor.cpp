// Fill out your copyright notice in the Description page of Project Settings.


#include "PNShurikenActor.h"

// Sets default values
APNShurikenActor::APNShurikenActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/Props/SM_Shuriken.SM_Shuriken'"));
	if (MeshFinder.Succeeded())
		StaticMeshComp->SetStaticMesh(MeshFinder.Object);

	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void APNShurikenActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APNShurikenActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location.X += 2.0;
	SetActorLocation(Location);
}

