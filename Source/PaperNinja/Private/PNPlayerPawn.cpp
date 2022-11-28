// Fill out your copyright notice in the Description page of Project Settings.


#include "PNPlayerPawn.h"
#include "PNGameMode.h"
#include "PNFuncLibrary.h"
#include "PNPickupCoinActor.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APNPlayerPawn::APNPlayerPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	Tags.Add(TEXT("Player"));
	bDead = false;
	NumOfCoins = 0;
	bHasScroll = false;
	GroundWalkSpeed = 150;
	GroundSprintSpeed = 200;

	GetCapsuleComponent()->SetCapsuleHalfHeight(44.0f);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/Characters/SK_Ninja.SK_Ninja'"));
	if (MeshFinder.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -44.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	GetMesh()->SetMobility(EComponentMobility::Movable);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimFinder(TEXT("AnimBlueprint'/Game/Animations/PNAnimBP_Ninja.PNAnimBP_Ninja'"));
	if (AnimFinder.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimFinder.Object->GetAnimBlueprintGeneratedClass());

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->SetRelativeRotation(FRotator(-40.0, 0.0, 0.0));
	SpringArmComp->TargetArmLength = 1500.0f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->FieldOfView = 50.0f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = GroundWalkSpeed;
	GetCharacterMovement()->MaxAcceleration = 600;

	DeathFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeathFX"));
	DeathFX->SetupAttachment(GetMesh(), TEXT("spine"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> DeathFXFinder(TEXT("ParticleSystem'/Game/Particles/PS_PlayerDeath.PS_PlayerDeath'"));
	if (DeathFXFinder.Object)
		DeathFX->SetTemplate(DeathFXFinder.Object);
	DeathFX->SetAutoActivate(false);

	PointLight_R = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight_R"));
	PointLight_R->SetupAttachment(GetMesh(), TEXT("right_ear03"));
	PointLight_R->SetIntensity(50.0f);
	PointLight_R->SetAttenuationRadius(200.0f);
	PointLight_R->SetLightColor(FLinearColor(0.39f, 1.0f, 0.16f));
	PointLight_R->SetCastShadows(false);

	PointLight_L = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight_L"));
	PointLight_L->SetupAttachment(GetMesh(), TEXT("left_ear03"));
	PointLight_L->SetIntensity(50.0f);
	PointLight_L->SetAttenuationRadius(200.0f);
	PointLight_L->SetLightColor(FLinearColor(0.39f, 1.0f, 0.16f));
	PointLight_L->SetCastShadows(false);
}

// Called when the game starts or when spawned
void APNPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle timer_handle;
	GetWorldTimerManager().SetTimer(timer_handle, this, &APNPlayerPawn::CheckSprintRisk, 0.5f, true);
}

// Called every frame
void APNPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APNPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APNPlayerPawn::PressedSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APNPlayerPawn::ReleasedSprint);
	PlayerInputComponent->BindAxis("LookUp", this, &APNPlayerPawn::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &APNPlayerPawn::LookRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APNPlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APNPlayerPawn::MoveRight);
}

float APNPlayerPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!bDead)
	{
		bDead = true;
		UKismetSystemLibrary::PrintString(this, TEXT("Died"));
		GetCharacterMovement()->DisableMovement();
		SetLifeSpan(5.0f);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetMesh()->SetSimulatePhysics(true);
		DropAllCoin();
		DeathFX->Activate();
		USoundBase* DeathSE = LoadObject<USoundBase>(NULL, TEXT("SoundCue'/Game/Audio/player_death_Cue.player_death_Cue'"));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSE, GetActorLocation());

		FTimerHandle TimerHandle;
		FTimerDelegate PlayJingle;
		PlayJingle.BindLambda(
			[this]()
			{
				APNGameMode* GameMode = CastChecked<APNGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
				USoundBase* Jingle = LoadObject<USoundBase>(NULL, TEXT("SoundCue'/Game/Audio/bgm03_Cue.bgm03_Cue'"));
				GameMode->PlayBGM(Jingle);
			}
		);
		GetWorldTimerManager().SetTimer(TimerHandle, PlayJingle, 1.0f, false);
	}

	return 0.0f;
}

void APNPlayerPawn::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APNPlayerPawn::LookRight(float Value)
{
	AddControllerYawInput(Value);
}

void APNPlayerPawn::MoveForward(float Value)
{
	FVector Forward = UPNFuncLibrary::FlattenDirection(CameraComp->GetForwardVector());
	AddMovementInput(Forward, Value);
}

void APNPlayerPawn::MoveRight(float Value)
{
	FVector Right = UPNFuncLibrary::FlattenVector(CameraComp->GetRightVector());
	AddMovementInput(Right, Value);
}

void APNPlayerPawn::PressedSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = GroundSprintSpeed;
}

void APNPlayerPawn::ReleasedSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = GroundWalkSpeed;
}

void APNPlayerPawn::CheckSprintRisk()
{
	double FlatSpeed = UPNFuncLibrary::FlattenVector(GetVelocity()).Length();
	if (FlatSpeed >= GroundSprintSpeed)
	{
		DropCoin();
	}
}

void APNPlayerPawn::AddCoin(int Num)
{
	NumOfCoins += Num;
	USoundBase* CoinGetSE = LoadObject<USoundBase>(NULL, TEXT("SoundCue'/Game/Audio/obj_coin_get_Cue.obj_coin_get_Cue'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoinGetSE, GetActorLocation());
}

void APNPlayerPawn::DropCoin()
{
	if (NumOfCoins > 0)
	{
		NumOfCoins--;
		const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName(TEXT("CoinSpawnPoint"));
		if (Socket)
		{
			FTransform SocketTransform = Socket->GetSocketTransform(GetMesh());
			APNPickupCoinActor* Coin = GetWorld()->SpawnActor<APNPickupCoinActor>(APNPickupCoinActor::StaticClass(), SocketTransform);
			FVector Impulse = FVector(200.0, 0.0, 200.0).RotateAngleAxis(UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f), FVector(0.0, 0.0, 1.0));
			Coin->StaticMeshComp->SetSimulatePhysics(true);
			Coin->StaticMeshComp->AddImpulse(Impulse, NAME_None, true);
		}
	}
}

void APNPlayerPawn::DropAllCoin()
{
	while (NumOfCoins > 0)
	{
		DropCoin();
	}
}

int APNPlayerPawn::GetNumOfCoins() const
{
	return NumOfCoins;
}

void APNPlayerPawn::ObtainScroll()
{
	GetCharacterMovement()->DisableMovement();
	bHasScroll = true;
	USoundBase* ScrollGetSE = LoadObject<USoundBase>(NULL, TEXT("SoundCue'/Game/Audio/obj_scroll_get_Cue.obj_scroll_get_Cue'"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ScrollGetSE, GetActorLocation());
	FTimerHandle TimerHandle;
	FTimerDelegate PlayJingle;
	PlayJingle.BindLambda(
		[this]()
		{
			APNGameMode* GameMode = CastChecked<APNGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			USoundBase* Jingle = LoadObject<USoundBase>(NULL, TEXT("SoundCue'/Game/Audio/bgm04_Cue.bgm04_Cue'"));
			GameMode->PlayBGM(Jingle);
		}
	);
	GetWorldTimerManager().SetTimer(TimerHandle, PlayJingle, 5.0f, false);
}