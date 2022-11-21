// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PNAIController.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API APNAIController : public AAIController
{
	GENERATED_BODY()

public:
	APNAIController();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		FVector GetPatrolLocation() const;

	UFUNCTION(BlueprintCallable)
		void PopPatrolLocation();

private:
	UFUNCTION()
		void GoToPatrol();

private:
	UPROPERTY()
		UBlackboardComponent* BlackboardComp;

	UPROPERTY()
		TArray<AActor*> AI_PatrollPoints;

	UPROPERTY()
		int PatrolIndex;
};
