// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Test_Event_Switch.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API ATest_Event_Switch : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		class APNGateActor* GateActor;

	UPROPERTY(EditDefaultsOnly)
		class APNSwitchActor* SwitchActor;
};
