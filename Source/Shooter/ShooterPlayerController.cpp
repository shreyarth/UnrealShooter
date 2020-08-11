// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay() {
	Super::BeginPlay();
	HUD = CreateWidget(this, HUDClass);
	HUD->AddToViewport();
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool IsWinner) {
	Super::GameHasEnded(EndGameFocus, IsWinner);
	HUD->RemoveFromViewport();
	if (IsWinner) {
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr) {
			WinScreen->AddToViewport();
		}
	}
	else {
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr) {
			LoseScreen->AddToViewport();
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}