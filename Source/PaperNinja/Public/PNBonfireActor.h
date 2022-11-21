// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "PNBonfireActor.generated.h"

UCLASS()
class PAPERNINJA_API APNBonfireActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APNBonfireActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		UStaticMeshComponent* MeshComp;

	UPROPERTY()
		UParticleSystemComponent* FireFXComp;

	UPROPERTY()
		UPointLightComponent* PointLight;

	UPROPERTY()
		UAudioComponent* AudioComp;
};
