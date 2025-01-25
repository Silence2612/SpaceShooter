// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool Deadcheck() const;

	UPROPERTY(EditDefaultsOnly)
	// float AcceptanceRadius = 200;
	class UBehaviorTree* AiBehavior;
};

