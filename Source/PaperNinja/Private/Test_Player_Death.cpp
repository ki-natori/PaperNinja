// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_Player_Death.h"
#include "PNPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ATest_Player_Death::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InputComponent->BindKey(EKeys::K, IE_Pressed, this, &ATest_Player_Death::PressedK);
	InputComponent->BindKey(EKeys::C, IE_Pressed, this, &ATest_Player_Death::PressedC);
	InputComponent->BindKey(EKeys::V, IE_Pressed, this, &ATest_Player_Death::PressedV);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATest_Player_Death::DisplayNumOfCoins, 0.5f, true);
}

void ATest_Player_Death::DisplayNumOfCoins()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APNPlayerPawn* PlayerPawn = Cast<APNPlayerPawn>(Pawn);
	if (PlayerPawn)
	{
		int NumOfCoins = PlayerPawn->GetNumOfCoins();
		UKismetSystemLibrary::PrintString(this, FString::FromInt(NumOfCoins));
	}
}

void ATest_Player_Death::PressedK()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UGameplayStatics::ApplyDamage(Pawn, 100.0f, NULL, this, UDamageType::StaticClass());
}

void ATest_Player_Death::PressedC()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APNPlayerPawn* PlayerPawn = Cast<APNPlayerPawn>(Pawn);
	if (PlayerPawn)
		PlayerPawn->AddCoin(5.0f);
}

void ATest_Player_Death::PressedV()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APNPlayerPawn* PlayerPawn = Cast<APNPlayerPawn>(Pawn);
	if (PlayerPawn)
		PlayerPawn->DropCoin();
}