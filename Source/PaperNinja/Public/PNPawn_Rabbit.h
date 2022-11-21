// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PNPawn_Rabbit.generated.h"

UCLASS()
class PAPERNINJA_API APNPawn_Rabbit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APNPawn_Rabbit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void BeginSprint();

	UFUNCTION(BlueprintCallable)
		void EndSprint();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		void CanSeePlayerPawn(bool& bResult, AActor*& SeenActor);

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);	

public:
	UPROPERTY(BlueprintReadOnly)
		bool bIsSprint;

	UPROPERTY(EditAnywhere, Category = "Chara Spec")
		float WalkGroundSpeed;

	UPROPERTY(EditAnywhere, Category = "Chara Spec")
		float SprintGroundSpeed;

	UPROPERTY(EditAnywhere, Category = "AI")
		TArray<AActor*> PatrolPoints;

	UPROPERTY(EditAnywhere, Category = "AI")
		float PatrolWaitDuration;

private:
	UPROPERTY()
		float SightLength;
};
