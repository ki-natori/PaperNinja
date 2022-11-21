// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Components/TimelineComponent.h"
#include "PNGateActor.generated.h"

UCLASS()
class PAPERNINJA_API APNGateActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APNGateActor();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void Open();

	UFUNCTION()
		void Close();

private:
	UFUNCTION()
		void UpdateOpening(FVector Value);

	UFUNCTION()
		void PlaySE();

		void InitSMComponent(UStaticMeshComponent* StaticMeshComponent, FName CompName, const TCHAR* MeshPath, FVector Location);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* OutsideLeftMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* InsideLeftMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* InsideRightMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* OutsideRightMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTimelineComponent* GateTimeline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UAudioComponent* Speaker;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;
};
