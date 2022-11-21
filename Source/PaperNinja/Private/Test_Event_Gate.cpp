#include "Test_Event_Gate.h"
#include "Kismet/GameplayStatics.h"
#include "PNGateActor.h"
#include "PNSwitchActor.h"

ATest_Event_Gate::ATest_Event_Gate()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATest_Event_Gate::BeginPlay()
{
	Super::BeginPlay();

	{
		TArray<AActor*> Gates;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APNGateActor::StaticClass(), Gates);
		if (Gates.Num())
			GateActor = CastChecked<APNGateActor>(Gates[0]);
	}
	{
		TArray<AActor*> Switches;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APNGateActor::StaticClass(), Switches);
		if (Switches.Num())
			SwitchActor = CastChecked<APNSwitchActor>(Switches[0]);
	}

	if (GateActor)
	{
		EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		InputComponent->BindKey(EKeys::O, IE_Pressed, GateActor, &APNGateActor::Open);
		InputComponent->BindKey(EKeys::O, IE_Released, GateActor, &APNGateActor::Close);
	}

	if (SwitchActor)
	{
		SwitchActor->OnTurnedOn.AddDynamic(this, &ATest_Event_Gate::TurnOnSwitch);
		SwitchActor->OnTurnedOff.AddDynamic(GateActor, &APNGateActor::Close);
	}
}

void ATest_Event_Gate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATest_Event_Gate::TurnOnSwitch()
{
	if (GateActor)
		GateActor->Open();

	GetWorldTimerManager().SetTimer(TimerHandle, SwitchActor, &APNSwitchActor::TurnOff, 3.0f, false);
}