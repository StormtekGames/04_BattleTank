// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	ATank* tank = GetControlledTank();

	if (tank != nullptr)
	{
		FString tankName = tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *tankName);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	
}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController is ticking infinitely."));
	AimTowardsCrosshair();
}

// Get world location of the linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector & HitLocation) const
{	
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	
	FVector2D ScreenLocation;
	ScreenLocation.X = ViewportSizeX * CrossHairXLocation;
	ScreenLocation.Y = ViewportSizeY * CrossHairYLocation;
	
	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, OUT LookDirection)) {
		// Line-trace along that look direction and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OUT HitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OUT LookDirection) const 
{
	FVector CameraWorldLocation;	// To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OUT HitLocation) const
{
	FHitResult OutHit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FCollisionResponseParams CollisionResponseParams;

	if (GetWorld()->LineTraceSingleByChannel(
		OutHit,
		StartLocation,
		EndLocation,
		ECC_Visibility)) {	
		HitLocation = OutHit.Location;
		return true;
	}
	HitLocation = FVector::ZeroVector;
	return false; // Line trace didn't succeed
}

// Start the tank moving the barrel so that a shot would hit where the crosshair
// intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{	
	if (!GetControlledTank()) { return; }

	OUT FVector HitLocation; // Out parameter
	
	if (GetSightRayHitLocation(OUT HitLocation)) {	// Has "side-effect", is going to line trace
		// TODO Tell controlled tank to aim at this point
		GetControlledTank()->TankAimingComponent->AimAt(HitLocation, GetControlledTank()->LaunchSpeed);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}