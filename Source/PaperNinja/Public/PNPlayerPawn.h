// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "PNPlayerPawn.generated.h"

UCLASS()
class PAPERNINJA_API APNPlayerPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APNPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
		void LookRight(float Value);

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void PressedSprint();

	UFUNCTION()
		void ReleasedSprint();

	UFUNCTION()
		void CheckSprintRisk();

	UFUNCTION()
		void AddCoin(int Num);

	UFUNCTION()
		void DropCoin();

	UFUNCTION()
		void DropAllCoin();

	UFUNCTION(BlueprintCallable)
		int GetNumOfCoins() const;

	UFUNCTION()
		void ObtainScroll();

public:
	UPROPERTY(BlueprintReadOnly)
		bool bHasScroll;

private:
	UPROPERTY()
		bool bDead;

	UPROPERTY()
		int NumOfCoins;

	UPROPERTY()
		float GroundWalkSpeed;

	UPROPERTY()
		float GroundSprintSpeed;

	UPROPERTY()
		UCameraComponent* CameraComp;

	UPROPERTY()
		USpringArmComponent* SpringArmComp;

	UPROPERTY()
		UParticleSystemComponent* DeathFX;

	UPROPERTY()
		UPointLightComponent* PointLight_R;

	UPROPERTY()
		UPointLightComponent* PointLight_L;
};
