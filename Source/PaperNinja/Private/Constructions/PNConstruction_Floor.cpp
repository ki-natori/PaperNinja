// Fill out your copyright notice in the Description page of Project Settings.


#include "Constructions/PNConstruction_Floor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APNConstruction_Floor::APNConstruction_Floor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidthCount = 1;
	LengthCount = 1;
	StaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Game/Architecture/SM_Floor.SM_Floor'"));

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetMobility(EComponentMobility::Static);
	RootComponent = SceneRoot;
}

void APNConstruction_Floor::OnConstruction(const FTransform& Transform)
{
	for (UStaticMeshComponent* Mesh : Meshes)
		Mesh->DestroyComponent();
	Meshes.Empty();

	Super::OnConstruction(Transform);
	for (int WidthIndex = 0; WidthIndex < WidthCount; WidthIndex++)
	{
		for (int LengthIndex = 0; LengthIndex < LengthCount; LengthIndex++)
		{
			UStaticMeshComponent* NewMesh = NewObject<UStaticMeshComponent>(this);
			NewMesh->SetupAttachment(SceneRoot);
			NewMesh->RegisterComponent();
			NewMesh->SetMobility(EComponentMobility::Movable);

			FRotator Rotation(
				0.0,
				UKismetMathLibrary::RandomFloat() < 0.2f ? 180.0 : 0.0,
				0.0
			);
			NewMesh->SetRelativeRotation(Rotation);

			FVector Location((double)WidthIndex * 100.0, (double)LengthIndex * 100.0, 0.0);
			NewMesh->SetRelativeLocation(Location);
			Meshes.Add(NewMesh);

			if (StaticMesh)
				NewMesh->SetStaticMesh(StaticMesh);
		}
	}
}

// Called when the game starts or when spawned
void APNConstruction_Floor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APNConstruction_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

