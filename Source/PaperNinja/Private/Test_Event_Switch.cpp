// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Event_Switch.h"
#include "PNGateActor.h"
#include "PNSwitchActor.h"
#include "Kismet/GameplayStatics.h"

void ATest_Event_Switch::BeginPlay()
{
	{
		TArray<AActor*> Gates;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APNGateActor::StaticClass(), Gates);
		if (Gates.Num())
			GateActor = CastChecked<APNGateActor>(Gates[0]);
	}
	{
		TArray<AActor*> Switches;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APNSwitchActor::StaticClass(), Switches);
		if (Switches.Num())
			SwitchActor = CastChecked<APNSwitchActor>(Switches[0]);
	}

	if (GateActor && SwitchActor)
	{
		SwitchActor->OnTurnedOn.AddDynamic(GateActor, &APNGateActor::Open);
	}
}