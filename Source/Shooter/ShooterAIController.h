// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	APawn* PlayerPawn;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* AIBehavior;

public:
	// Sets default values for this character's properties
	AShooterAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
