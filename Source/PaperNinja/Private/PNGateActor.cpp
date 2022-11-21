// Fill out your copyright notice in the Description page of Project Settings.


#include "PNGateActor.h"
#include "Components/AudioComponent.h"
#include "Curves/CurveVector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APNGateActor::APNGateActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = Arrow;

	InitSMComponent(OutsideLeftMesh, TEXT("OutsideLeftMesh"), TEXT("StaticMesh'/Game/Architecture/SM_Fusuma02_01.SM_Fusuma02_01'"), FVector(0.0, 75.0, 0.0));
	InitSMComponent(InsideLeftMesh, TEXT("InsideLeftMesh"), TEXT("StaticMesh'/Game/Architecture/SM_Fusuma02_01.SM_Fusuma02_02'"), FVector(0.0, 25.0, 0.0));
	InitSMComponent(OutsideLeftMesh, TEXT("InsideRightMesh"), TEXT("StaticMesh'/Game/Architecture/SM_Fusuma02_01.SM_Fusuma02_03'"), FVector(0.0, -25.0, 0.0));
	InitSMComponent(OutsideLeftMesh, TEXT("OutsideRightMesh"), TEXT("StaticMesh'/Game/Architecture/SM_Fusuma02_01.SM_Fusuma02_04'"), FVector(0.0, -75.0, 0.0));

	GateTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("GateTimeline"));
	if (GateTimeline)
	{
		GateTimeline->SetTimelineLength(1.0f);
		GateTimeline->SetLooping(false);
		EObjectFlags Flags = EObjectFlags::RF_Public
			| EObjectFlags::RF_Transactional
			| EObjectFlags::RF_WasLoaded
			| EObjectFlags::RF_LoadCompleted;
		UCurveVector* CurveVector = NewObject<UCurveVector>(this, UCurveVector::StaticClass(), TEXT("Left"), Flags);
		if (CurveVector)
		{
			FKeyHandle KeyX00 = CurveVector->FloatCurves[0].AddKey(0.0f, 0.0f);
			CurveVector->FloatCurves[0].AddKey(0.5f, -10.0f);
			CurveVector->FloatCurves[0].SetKeyInterpMode(KeyX00, ERichCurveInterpMode::RCIM_Cubic);

			FKeyHandle KeyY05 = CurveVector->FloatCurves[1].AddKey(0.5f, 25.0f);
			CurveVector->FloatCurves[1].AddKey(1.0f, 75.0f);
			CurveVector->FloatCurves[1].SetKeyInterpMode(KeyY05, ERichCurveInterpMode::RCIM_Cubic);

			CurveVector->FloatCurves[2].AddKey(0.0f, 0.0f);
		}

		FOnTimelineVector UpdateFunc;
		UpdateFunc.BindUFunction(this, TEXT("UpdateOpening"));
		GateTimeline->AddInterpVector(CurveVector, UpdateFunc);

		FOnTimelineEvent Opening;
		Opening.BindUFunction(this, TEXT("PlaySE"));
		GateTimeline->AddEvent(0.5f, Opening);
	}

	Speaker = CreateDefaultSubobject<UAudioComponent>(TEXT("Speaker"));
	Speaker->SetupAttachment(RootComponent);
	Speaker->SetRelativeLocation(FVector(0.0, 0.0, 50.0));
	USoundBase* Cue = LoadObject<USoundBase>(NULL, TEXT("SoundCue'/Game/Audio/Gate_Cue.Gate_Cue'"));
	Speaker->SetSound(Cue);
	Speaker->SetAutoActivate(false);
}

void APNGateActor::BeginPlay()
{
	Super::BeginPlay();

	GateTimeline->SetPropertySetObject(this);
	GateTimeline->SetDirectionPropertyName(TEXT("TimelineDirection"));
}

void APNGateActor::Open()
{
	if (GateTimeline)
		GateTimeline->Play();
}

void APNGateActor::Close()
{
	if (GateTimeline)
	{
		Speaker->SetIntParameter(TEXT("SE Type"), 2);
		Speaker->Play();
		GateTimeline->Reverse();
	}
}

void APNGateActor::UpdateOpening(FVector Value)
{
	InsideLeftMesh->SetRelativeLocation(Value);
	InsideRightMesh->SetRelativeLocation(Value * FVector(1.0, -1.0, 1.0));
}

void APNGateActor::PlaySE()
{
	Speaker->SetIntParameter(TEXT("SE Type"), TimelineDirection == ETimelineDirection::Forward ? 0 : 1);
	Speaker->Play();
}

void APNGateActor::InitSMComponent(UStaticMeshComponent* StaticMeshComponent, FName CompName, const TCHAR* MeshPath, FVector Location)
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(CompName);
	StaticMeshComponent->SetupAttachment(RootComponent);
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(NULL, MeshPath);
	if (Mesh)
		StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->SetRelativeLocation(Location);
}