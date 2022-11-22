// Fill out your copyright notice in the Description page of Project Settings.


#include "PNTitleMode.h"
#include "PNTitlePlayerController.h"

APNTitleMode::APNTitleMode()
{
	PlayerControllerClass = APNTitlePlayerController::StaticClass();
}