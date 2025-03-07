// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> gunClass;
	
	UPROPERTY(EditDefaultsOnly)
		float MaxHP = 100.f;
	UPROPERTY(VisibleAnywhere)
		float Health;
	UPROPERTY(EditDefaultsOnly)
		float WalkSpeed = 50.f;
	UPROPERTY(EditDefaultsOnly)
		float SprintSpeed = 100.f;


	void MoveForward(float val);
	void MoveRight(float val);
	//void LookUp(float val);

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	UPROPERTY()
		AGun* gun;
	void Shoot();
	void Reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	UFUNCTION(BlueprintPure)
		float GetHP() const;
	
	UFUNCTION(BlueprintPure)
		int32 GetAmmo();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
