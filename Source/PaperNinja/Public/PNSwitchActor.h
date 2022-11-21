// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "PNSwitchActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSwitchDelegate);

UCLASS()
class PAPERNINJA_API APNSwitchActor : public AActor
{
	GENERATED_BODY()

public:
	APNSwitchActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void TurnOff();

private:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void UpdateTimeline(float Value);

	UFUNCTION()
		void FinishTimeline();

public:
	UPROPERTY(EditAnywhere)
		bool bIsMomentary;

	UPROPERTY()
		TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY(BlueprintAssignable)
		FSwitchDelegate OnTurnedOn;

	UPROPERTY(BlueprintAssignable)
		FSwitchDelegate OnTurnedOff;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* ButtonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTimelineComponent* TimelineComp;

private:
	UPROPERTY()
		UMaterialInstanceDynamic* MeshMID;
};
