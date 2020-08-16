// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "Gun.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot() {
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) { return EBTNodeResult::Failed; }

	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(Character == nullptr){ return EBTNodeResult::Failed; }
	if (Character->gun->Ammo <= 0) { Character->Reload(); }
	Character->Shoot();

	return EBTNodeResult::Succeeded;
}
