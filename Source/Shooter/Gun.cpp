// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	gunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));
	SetRootComponent(gunRoot);

	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	gunMesh->SetupAttachment(gunRoot);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AController* AGun::GetOwnerController() const {
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr) { return nullptr; }
	return ownerPawn->GetController();
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) {
	AController* ownerController = GetOwnerController();
	if (ownerController == nullptr) { return false; }

	FVector location;
	FRotator rotation;
	ownerController->GetPlayerViewPoint(location, rotation);
	ShotDirection = -rotation.Vector();

	FVector endPoint = location + rotation.Vector() * maxRange;
	//TODO: Line Trace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, location, endPoint, ECC_GameTraceChannel1, Params);
}

void AGun::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("AHHH I GOT SHOT"));
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, gunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, gunMesh, TEXT("MuzzleFlashSocket"));

	FHitResult hit_result;
	FVector shotDirection;
	bool bHit = GunTrace(hit_result, shotDirection);
	if (bHit) {
		//DrawDebugPoint(GetWorld(), hit_result.Location, 30, FColor::Red, bHit);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, hit_result.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, hit_result.Location, shotDirection.Rotation(), 0.5f);
		AActor* actorHit = hit_result.GetActor();
		if (actorHit) {
			FPointDamageEvent DamageEvent(damage, hit_result, shotDirection, nullptr);
			AController* ownerController = GetOwnerController();
			actorHit->TakeDamage(damage, DamageEvent, ownerController, this);
		}
	}
}

