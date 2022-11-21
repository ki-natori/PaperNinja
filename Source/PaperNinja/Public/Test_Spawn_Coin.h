// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Test_Spawn_Coin.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API ATest_Spawn_Coin : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void SpawnCoin();

private:
	UPROPERTY(EditDefaultsOnly)
		class ATargetPoint* CoinSpawnPoint;

	UPROPERTY(EditDefaultsOnly)
		class APNSwitchActor* SwitchActor;
};
