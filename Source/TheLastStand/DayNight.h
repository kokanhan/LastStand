// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "DayNight.generated.h"

UCLASS()
class THELASTSTAND_API ADayNight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnEnemy();
	void RepeatingFunction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category = "Sky")
	AActor* Sun;
	UPROPERTY(EditAnywhere, Category = "Sky")
	ADirectionalLight* LightSource;
	UPROPERTY(EditAnywhere, Category = "Sky")
	float TurnRate;
	UPROPERTY(EditAnywhere, Category = "Sky")
	AActor* MoonLight;

	FTimerHandle MemberTimerHandle;
	bool IsNight;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawn Number and Speed")
	float EnemyCrowdSpeed = 1.f;
	int EnemyTotal = 10;
	float SpawnSpeedDelay = 2.f;
};
