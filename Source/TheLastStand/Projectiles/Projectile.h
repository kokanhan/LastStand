// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class THELASTSTAND_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	bool isAnimating;

protected:
	FVector InitialVelocity;
	FVector InitialPosition;
	FVector TargetPosition;
	float Gravity = -980.f;
	float LaunchSpeed = 1000.f;
	float LaunchAngle;
	float TimeElapsed;
	float FlyDuration;

private:
	int type;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void activeProjectile(int curType, FVector startPos, FVector TargetLocation, float spd = 1000);
	void castExplosionEffect();

	void setSpeed(float targetSpd);

private:
	float CalculateFlightTime(float InitialVelocityZ, float HeightDifference);
	void CalculateLaunchParameters();

	bool highShoot;
};
