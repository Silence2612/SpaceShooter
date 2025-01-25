// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_shoot.h"
#include "MyCharacter.h"
#include "AIController.h"


UBTTask_shoot::UBTTask_shoot()
{
    NodeName = TEXT("AI Shoot");
}

EBTNodeResult::Type UBTTask_shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp , NodeMemory);
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AMyCharacter* Character = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->Shoot();

    return EBTNodeResult::Succeeded;

}

