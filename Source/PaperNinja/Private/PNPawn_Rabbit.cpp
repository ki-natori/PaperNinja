// Fill out your copyright notice in the Description page of Project Settings.


#include "PNPawn_Rabbit.h"
#include "PNAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APNPawn_Rabbit::APNPawn_Rabbit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	PatrolWaitDuration = 1.0f;
	SightLength = 300.0f;
	WalkGroundSpeed = 100;
	SprintGroundSpeed = 220;
	bIsSprint = false;

	AIControllerClass = APNAIController::StaticClass();

	GetCapsuleComponent()->SetCapsuleHalfHeight(44.0f);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/Characters/SK_Rabbit.SK_Rabbit'"));
	if (MeshFinder.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -44.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetMobility(EComponentMobility::Movable);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimFinder(TEXT("AnimBlueprint'/Game/Animations/PNAnimBP_Rabbit.PNAnimBP_Rabbit'"));
	if (AnimFinder.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimFinder.Object->GetAnimBlueprintGeneratedClass());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxAcceleration = 150;
}

// Called when the game starts or when spawned
void APNPawn_Rabbit::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APNPawn_Rabbit::OnHit);
	GetCharacterMovement()->MaxWalkSpeed = WalkGroundSpeed;
	GetWorld()->DebugDrawTraceTag = FName("Sight");
}

// Called every frame
void APNPawn_Rabbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprint)
	{
		FHitResult HitResult;
		FVector Start = GetMesh()->GetSocketLocation(TEXT("spine"));
		FVector End = Start + (GetActorForwardVector() * 50.0f);
		const FName TraceTag("Sight");
		FCollisionQueryParams Params;
		Params.TraceTag = TraceTag;
		Params.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), 100.0f, NULL, this, UDamageType::StaticClass());
		}
	}
}

// Called to bind functionality to input
void APNPawn_Rabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APNPawn_Rabbit::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintGroundSpeed;
	bIsSprint = true;
}

void APNPawn_Rabbit::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkGroundSpeed;
	bIsSprint = false;
}

void APNPawn_Rabbit::CanSeePlayerPawn(bool& bResult, AActor*& SeenActor)
{
	SeenActor = NULL;
	bResult = false;

	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * SightLength);
	const FName TraceTag("Sight");
	FCollisionQueryParams Params;
	Params.TraceTag = TraceTag;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
		SeenActor = HitResult.GetActor();

	bResult = (SeenActor && SeenActor->ActorHasTag(TEXT("Player")));
}

void APNPawn_Rabbit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, 100.0f, NULL, this, UDamageType::StaticClass());
}