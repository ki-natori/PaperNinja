// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Actor_Movement.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ATest_Actor_Movement::ATest_Actor_Movement()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATest_Actor_Movement::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SMShurikenActor"), Actors);

	Shuriken = Actors[0];

	if (!Shuriken)
		SetActorTickEnabled(false);
}

void ATest_Actor_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = Shuriken->GetActorLocation();
	Location.X += 2.0;
	Shuriken->SetActorLocation(Location);
}