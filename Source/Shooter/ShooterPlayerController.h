// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(AActor* EndGameFocus = nullptr, bool IsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDClass;

	UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.0f;

	FTimerHandle RestartTimer;

protected:
	virtual void BeginPlay() override;
};
