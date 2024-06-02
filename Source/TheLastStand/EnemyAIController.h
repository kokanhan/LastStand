// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	float DetectionRange = 200.f;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	/*UPROPERTY(EditAnywhere)
	class AActor* tt;*/
};
