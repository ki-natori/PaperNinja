// Fill out your copyright notice in the Description page of Project Settings.


#include "PNPickupCoinActor.h"
#include "PNPlayerPawn.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APNPickupCoinActor::APNPickupCoinActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bEnable = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/Props/SM_Coin.SM_Coin'"));
	if (MeshFinder.Succeeded())
		StaticMeshComp->SetStaticMesh(MeshFinder.Object);
	StaticMeshComp->SetMobility(EComponentMobility::Movable);
	StaticMeshComp->SetCollisionProfileName(TEXT("Pickup"));
	RootComponent = StaticMeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(StaticMeshComp);
	BoxComp->SetRelativeLocation(FVector(0.0, 0.0, 25.0));
	BoxComp->SetBoxExtent(FVector(25.0, 25.0, 25.0));

	EObjectFlags Flags = EObjectFlags::RF_Public
		| EObjectFlags::RF_Transactional
		| EObjectFlags::RF_WasLoaded
		| EObjectFlags::RF_LoadCompleted;

	UCurveFloat* CurveFloat = NewObject<UCurveFloat>(this, UCurveFloat::StaticClass(), TEXT("CoinYaw"), Flags);
	if (CurveFloat)
	{
		CurveFloat->FloatCurve.AddKey(0.0f, 0.0f);
		CurveFloat->FloatCurve.AddKey(1.0f, 360.0f);
	}

	TimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("CoinRotationTimeline"));
	TimelineComp->SetTimelineLength(1.0f);
	TimelineComp->SetLooping(true);
	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindUFunction(this, TEXT("Rotate"));
	TimelineComp->AddInterpFloat(CurveFloat, UpdateFunc);

}

// Called when the game starts or when spawned
void APNPickupCoinActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNPickupCoinActor::OnOverlap);

	if (TimelineComp)
		TimelineComp->PlayFromStart();

	GetWorldTimerManager().SetTimer(EnableTimer, this, &APNPickupCoinActor::EnablePickup, 0.5f);
}

void APNPickupCoinActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bEnable)
		return;

	APNPlayerPawn* PlayerPawn = Cast<APNPlayerPawn>(OtherActor);
	if (PlayerPawn)
	{
		PlayerPawn->AddCoin(1.0f);
		Destroy();
		UParticleSystem* Particle = LoadObject<UParticleSystem>(NULL, TEXT("ParticleSystem'/Game/Particles/PS_Pickup_Coin.PS_Pickup_Coin'"));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, PlayerPawn->GetActorTransform());
	}
}

void APNPickupCoinActor::Rotate(float Value)
{
	StaticMeshComp->SetRelativeRotation(FRotator(0.0, Value, 0.0));
}

void APNPickupCoinActor::EnablePickup()
{
	bEnable = true;
}