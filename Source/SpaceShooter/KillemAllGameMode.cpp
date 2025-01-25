// Fill out your copyright notice in the Description page of Project Settings.


#include "KillemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "MyAIController.h"

void AKillemAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if(PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AMyAIController* Controller : TActorRange<AMyAIController>(GetWorld()))
    {
        if (!Controller->Deadcheck())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillemAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }

}
