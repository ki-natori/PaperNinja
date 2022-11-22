// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PNConstruction_Floor.generated.h"

UCLASS()
class PAPERNINJA_API APNConstruction_Floor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APNConstruction_Floor();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1"))
		int WidthCount;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1"))
		int LengthCount;

	UPROPERTY(EditAnywhere)
		UStaticMesh* StaticMesh;

private:
	UPROPERTY()
		USceneComponent* SceneRoot;

	UPROPERTY()
		TArray<UStaticMeshComponent*> Meshes;
};
