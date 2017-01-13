// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	ATank* tank = GetControlledTank();

	if (tank != nullptr)
	{
		FString tankName = tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Player is possessing %s"), *tankName);
	}
}
