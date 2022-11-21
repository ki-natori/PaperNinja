#include "PNStage01.h"
#include "PNGateActor.h"
#include "PNSwitchActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

APNStage01::APNStage01()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APNStage01::BeginPlay()
{
	Super::BeginPlay();

	{
		TArray<AActor*> Gates;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Fusuma01"), Gates);
		if (Gates.Num())
			Fusuma01 = Cast<APNGateActor>(Gates[0]);
	}
	{
		TArray<AActor*> Switches;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Fusuma01_SW"), Switches);
		if (Switches.Num())
			Fusuma01_SW = Cast<APNSwitchActor>(Switches[0]);
	}
	{
		TArray<AActor*> Gates;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Fusuma02"), Gates);
		if (Gates.Num())
			Fusuma02 = Cast<APNGateActor>(Gates[0]);
	}
	{
		TArray<AActor*> Switches;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Fusuma02_SW"), Switches);
		if (Switches.Num())
			Fusuma02_SW = Cast<APNSwitchActor>(Switches[0]);
	}

	if (Fusuma01 && Fusuma01_SW)
		Fusuma01_SW->OnTurnedOn.AddDynamic(Fusuma01, &APNGateActor::Open);

	if (Fusuma02 && Fusuma02_SW)
	{
		Fusuma02_SW->OnTurnedOn.AddDynamic(this, &APNStage01::OpenFusuma02);
		Fusuma02_SW->OnTurnedOff.AddDynamic(Fusuma02, &APNGateActor::Close);
	}
}

void APNStage01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APNStage01::OpenFusuma02()
{
	if (Fusuma02)
	{
		Fusuma02->Open();

		GetWorldTimerManager().SetTimer(TimerHandle, Fusuma02_SW, &APNSwitchActor::TurnOff, 5.0f, false);
	}
}