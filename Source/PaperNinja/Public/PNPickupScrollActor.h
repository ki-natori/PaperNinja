// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PNPickupScrollActor.generated.h"

UCLASS()
class PAPERNINJA_API APNPickupScrollActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APNPickupScrollActor();

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
		USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;

	UPROPERTY()
		UParticleSystemComponent* FXComp;
};
