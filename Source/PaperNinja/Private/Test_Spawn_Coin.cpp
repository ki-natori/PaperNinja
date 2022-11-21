// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Spawn_Coin.h"
#include "PNSwitchActor.h"
#include "PNPickupCoinActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void ATest_Spawn_Coin::BeginPlay()
{
	{
		TArray<AActor*> Switches;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("PNSwitchActor"), Switches);
		if (Switches.Num())
			SwitchActor = CastChecked<APNSwitchActor>(Switches[0]);
	}
	{
		TArray<AActor*> Points;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("CoinSpawnPoint"), Points);
		if (Points.Num())
			CoinSpawnPoint = CastChecked<ATargetPoint>(Points[0]);
	}

	if (SwitchActor && CoinSpawnPoint)
		SwitchActor->OnTurnedOn.AddDynamic(this, &ATest_Spawn_Coin::SpawnCoin);
}

void ATest_Spawn_Coin::SpawnCoin()
{
	GetWorld()->SpawnActor<APNPickupCoinActor>(
		APNPickupCoinActor::StaticClass(),
		CoinSpawnPoint->GetActorTransform()
		);
}