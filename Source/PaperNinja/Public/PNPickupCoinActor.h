// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "PNPickupCoinActor.generated.h"

UCLASS()
class PAPERNINJA_API APNPickupCoinActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APNPickupCoinActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Rotate(float Value);

	UFUNCTION()
		void EnablePickup();

private:
	UPROPERTY()
		bool bEnable;

	UPROPERTY()
		FTimerHandle EnableTimer;

public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComp;

protected:
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
		UTimelineComponent* TimelineComp;
};
