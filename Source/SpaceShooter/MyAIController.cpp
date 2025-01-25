#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "MyCharacter.h"

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    // SetFocus(PlayerPawn);
    if(AiBehavior !=  nullptr){
        RunBehaviorTree(AiBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AMyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AMyAIController::Deadcheck() const
{
    AMyCharacter* ControlledCharacter = Cast<AMyCharacter>(GetPawn());
    if(ControlledCharacter != nullptr){
        return ControlledCharacter->Deadcheck();
    }
    return true;
}
