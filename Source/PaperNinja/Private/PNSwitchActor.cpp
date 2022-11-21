#include "PNSwitchActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

APNSwitchActor::APNSwitchActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneComp;

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ButtonMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonMeshFinder(TEXT("StaticMesh'/Game/Props/SM_Shape_Cylinder100x10.SM_Shape_Cylinder100x10'"));
	if (ButtonMeshFinder.Succeeded())
		ButtonMesh->SetStaticMesh(ButtonMeshFinder.Object);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxComp->SetupAttachment(ButtonMesh);
	BoxComp->InitBoxExtent(FVector(22.0, 22.0, 10.0));
	BoxComp->SetRelativeLocation(FVector(0.0, 0.0, 20.0));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshFinder(TEXT("StaticMesh'/Game/Props/SM_Shape_Cylinder_Base.SM_Shape_Cylinder_Base'"));
	if (BaseMeshFinder.Succeeded())
		BaseMesh->SetStaticMesh(BaseMeshFinder.Object);

	TimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("SwitchTimeline"));
	TimelineComp->SetTimelineLength(0.5f);
	TimelineComp->SetLooping(false);
	EObjectFlags Flags = EObjectFlags::RF_Public
		| EObjectFlags::RF_Transactional
		| EObjectFlags::RF_WasLoaded
		| EObjectFlags::RF_LoadCompleted;

	UCurveFloat* CurveFloat = NewObject<UCurveFloat>(this, UCurveFloat::StaticClass(), TEXT("Alpha"), Flags);
	CurveFloat->FloatCurve.AddKey(0.0f, 0.0f);
	CurveFloat->FloatCurve.AddKey(0.5f, 1.0f);

	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindDynamic(this, &APNSwitchActor::UpdateTimeline);
	TimelineComp->AddInterpFloat(CurveFloat, UpdateFunc);

	FOnTimelineEvent FinishFunc;
	FinishFunc.BindDynamic(this, &APNSwitchActor::FinishTimeline);
	TimelineComp->SetTimelineFinishedFunc(FinishFunc);
}

void APNSwitchActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNSwitchActor::OnOverlapBegin);
	if (bIsMomentary)
		BoxComp->OnComponentEndOverlap.AddDynamic(this, &APNSwitchActor::OnOverlapEnd);

	TimelineComp->SetPropertySetObject(this);
	TimelineComp->SetDirectionPropertyName(TEXT("TimelineDirection"));

	MeshMID = ButtonMesh->CreateDynamicMaterialInstance(0, ButtonMesh->GetMaterial(0));
	MeshMID->SetVectorParameterValue(TEXT("Tint Base Color"), FVector(1.0, 0.0, 0.0));
}

void APNSwitchActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APNSwitchActor::TurnOff()
{
	if (TimelineComp)
		TimelineComp->Reverse();
}

void APNSwitchActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TimelineComp)
		TimelineComp->Play();
}

void APNSwitchActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (TimelineComp)
		TimelineComp->Reverse();
}

void APNSwitchActor::UpdateTimeline(float Value)
{
	double NewZ = FMath::Lerp(0.0, -8.0, Value);
	ButtonMesh->SetRelativeLocation(FVector(0.0, 0.0, NewZ));
}

void APNSwitchActor::FinishTimeline()
{
	if (TimelineDirection == ETimelineDirection::Forward)
	{
		OnTurnedOn.Broadcast();
		MeshMID->SetVectorParameterValue(TEXT("Tint Base Color"), FVector(0.0, 1.0, 0.0));
	}
	else if (TimelineDirection == ETimelineDirection::Backward)
	{
		OnTurnedOff.Broadcast();
		MeshMID->SetVectorParameterValue(TEXT("Tint Base Color"), FVector(1.0, 0.0, 0.0));
	}
}