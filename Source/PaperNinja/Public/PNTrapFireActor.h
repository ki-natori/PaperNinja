// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PNTrapFireActor.generated.h"

UCLASS()
class PAPERNINJA_API APNTrapFireActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APNTrapFireActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystemComponent* ParticleSystemComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;
};
