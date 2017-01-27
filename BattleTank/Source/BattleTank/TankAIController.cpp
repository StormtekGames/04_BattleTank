// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATank* playerTank = nullptr;
	ATankPlayerController* playerController = (ATankPlayerController*)GetWorld()->GetFirstPlayerController();
	if (playerController != nullptr) {
		playerTank = playerController->GetControlledTank();
	}
	return playerTank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));

	ATank* tank = GetControlledTank();

	if (tank != nullptr) {
		FString tankName = tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController is possessing %s"), *tankName);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
	}

	ATank* playerTank = GetPlayerTank();

	if (playerTank != nullptr) {
		FString playerTankName = playerTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AIController is targetting Player's tank: %s"), *playerTankName);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController not targetting Player's tank."));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	ATank * playerTank = GetPlayerTank();

	if (playerTank != nullptr) {
		FVector PlayerHitLocation = playerTank->GetActorLocation();
		GetControlledTank()->TankAimingComponent->AimAt(PlayerHitLocation, GetControlledTank()->LaunchSpeed);

		// TODO Move towards the player

		// Aim towards the player

		// Fire if ready
	}
	
}

