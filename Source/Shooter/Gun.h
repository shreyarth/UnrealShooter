// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent * gunRoot;
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* gunMesh;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* muzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* hitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* HitSound;
	UPROPERTY(EditAnywhere)
		float maxRange = 1000.f;
	UPROPERTY(EditAnywhere)
		float damage = 10.f;
	
	UPROPERTY(EditDefaultsOnly)
		int32 DefaultAmmo;
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

public:	
	// Sets default values for this actor's properties
	AGun();

	UPROPERTY(EditDefaultsOnly)
		int32 Ammo = 50;
	void PullTrigger();
	void Reload();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
