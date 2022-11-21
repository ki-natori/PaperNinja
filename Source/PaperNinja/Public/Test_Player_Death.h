// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Test_Player_Death.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API ATest_Player_Death : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void DisplayNumOfCoins();

private:
	UFUNCTION()
		void PressedK();

	UFUNCTION()
		void PressedC();

	UFUNCTION()
		void PressedV();
};
