// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameMode.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AMyCharacter::Deadcheck() const
{
	if(Health<=0){
		return true;
	}
	return false;
}

float AMyCharacter::GetHealthPercent() const
{
	return (Health/MaxHealth);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r") , EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh() , FAttachmentTransformRules::KeepRelativeTransform , TEXT("Gun_Socket"));
	Gun->SetOwner(this);
	Health = MaxHealth;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward") , this , &AMyCharacter::MoveForward );
	PlayerInputComponent->BindAxis(TEXT("LookUp") , this , &AMyCharacter::LookUp );
	PlayerInputComponent->BindAxis(TEXT("MoveRight") , this , &AMyCharacter::MoveRight );
	PlayerInputComponent->BindAxis(TEXT("LookRight") , this , &AMyCharacter::LookRight );
	PlayerInputComponent->BindAxis(TEXT("LookUpRate") , this , &AMyCharacter::LookUpRate );
	PlayerInputComponent->BindAxis(TEXT("LookRightRate") , this , &AMyCharacter::LookRightRate );
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMyCharacter::Shoot);
}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount , DamageEvent , EventInstigator , DamageCauser);
	DamageToApply = FMath::Min(Health,DamageAmount);
	Health = Health - DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Current Health : %f") , Health);
	if(Deadcheck()){
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ASimpleShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameMode>();
		if(GameMode != nullptr){
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
	}
	return DamageToApply;
}

void AMyCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMyCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AMyCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AMyCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMyCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::Shoot()
{
	Gun->PullTrigger();
}




