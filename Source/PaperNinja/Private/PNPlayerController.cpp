// Fill out your copyright notice in the Description page of Project Settings.


#include "PNPlayerController.h"
#include "PNPlayerCameraManager.h"

APNPlayerController::APNPlayerController()
{
	PlayerCameraManagerClass = APNPlayerCameraManager::StaticClass();
}