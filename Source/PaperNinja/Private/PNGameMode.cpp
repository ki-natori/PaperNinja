// Fill out your copyright notice in the Description page of Project Settings.


#include "PNGameMode.h"
#include "PNPlayerPawn.h"
#include "PNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/AudioComponent.h"
#include "Blueprint/UserWidget.h"

APNGameMode::APNGameMode()
{
	DefaultPawnClass = APNPlayerPawn::StaticClass();
	PlayerControllerClass = APNPlayerController::StaticClass();
	MusicSpeaker = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicSpeaker"));
	MusicSpeaker->SetAutoActivate(false);

	ConstructorHelpers::FObjectFinder<USoundBase> BGMFinder(TEXT("SoundCue'/Game/Audio/bgm02_Cue.bgm02_Cue'"));
	if (BGMFinder.Succeeded())
		BGM = BGMFinder.Object;

	ConstructorHelpers::FObjectFinder<UBlueprint> HUDFinder(TEXT("WidgetBlueprint'/Game/Blueprints/PNGameHUD.PNGameHUD'"));
	if (HUDFinder.Succeeded())
		HUDWidget = HUDFinder.Object->GeneratedClass;
}

void APNGameMode::BeginPlay()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Pawn->OnDestroyed.AddDynamic(this, &APNGameMode::RespawnPlayer);
	PlayBGM(BGM);
	if (HUDWidget)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
		if (Widget)
			Widget->AddToViewport();
	}
}

void APNGameMode::PlayBGM(USoundBase* NewBGM)
{
	MusicSpeaker->Stop();
	MusicSpeaker->SetSound(NewBGM);
	MusicSpeaker->Play();
}

void APNGameMode::RespawnPlayer(AActor* DestroyedActor)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* PlayerStart = FindPlayerStart(Controller);
	APNPlayerPawn* NewPawn = GetWorld()->SpawnActor<APNPlayerPawn>(APNPlayerPawn::StaticClass(), PlayerStart->GetActorTransform());
	Controller->Possess(NewPawn);
	NewPawn->OnDestroyed.AddDynamic(this, &APNGameMode::RespawnPlayer);
	PlayBGM(BGM);
}