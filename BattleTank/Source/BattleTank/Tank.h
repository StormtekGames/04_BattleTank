// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

/// Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UPROPERTY(BlueprintReadWrite)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire() const;

	UPROPERTY(EditAnywhere, Category=Firing)
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint; // Alternative http://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/

private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// Local barrel reference for spawning projectiles
	UTankBarrel* Barrel = nullptr;
};
