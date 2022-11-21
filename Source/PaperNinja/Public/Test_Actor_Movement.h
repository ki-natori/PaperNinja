// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Test_Actor_Movement.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API ATest_Actor_Movement : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ATest_Actor_Movement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class AActor* Shuriken;
};
