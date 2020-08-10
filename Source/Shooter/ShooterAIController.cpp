// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

AShooterAIController::AShooterAIController() {

}


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);

}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToActor(PlayerPawn, 200);
}


