// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include
/// Forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
private:

	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	void AimTowardsCrosshair();
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 1.0f / 3.0f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10.0f * 1000.0f * 100.0f;	// 10 km (conversion from cm)
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OUT LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OUT HitLocation) const;
};
