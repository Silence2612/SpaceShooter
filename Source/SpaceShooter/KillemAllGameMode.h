// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameMode.h"
#include "KillemAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AKillemAllGameMode : public ASimpleShooterGameMode
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	
private:
	void EndGame(bool bIsPlayerWinner);
};
