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

void AGun::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("AHHH I GOT SHOT"));
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, gunMesh, TEXT("MuzzleFlashSocket"));

	FVector location;
	FRotator rotation;
	
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr) { return; }
	AController* ownerController = ownerPawn->GetController();
	if (ownerController == nullptr) { return; }
	ownerController->GetPlayerViewPoint(location, rotation);

	FVector endPoint = location + rotation.Vector() * maxRange;
	//TODO: Line Trace
	FHitResult hit_result;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bHit = GetWorld()->LineTraceSingleByChannel(hit_result, location, endPoint, ECC_GameTraceChannel1, Params);
	if (bHit) {
		//DrawDebugPoint(GetWorld(), hit_result.Location, 30, FColor::Red, bHit);
		FVector shotDirection = -rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, hit_result.Location, shotDirection.Rotation());
		AActor* actorHit = hit_result.GetActor();
		if (actorHit) {
			FPointDamageEvent DamageEvent(damage, hit_result, shotDirection, nullptr);
			actorHit->TakeDamage(damage, DamageEvent, ownerController, this);
		}
	}
}

