// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PNGameMode.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API APNGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APNGameMode();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void PlayBGM(USoundBase* NewBGM);
private:
	UFUNCTION()
		void RespawnPlayer(AActor* DestroyedActor);

private:
	UPROPERTY()
		UAudioComponent* MusicSpeaker;

	UPROPERTY()
		TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY()
		USoundBase* BGM;
};
