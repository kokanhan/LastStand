// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "qoqiuqiu.generated.h"

UCLASS()
class THELASTSTAND_API Aqoqiuqiu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aqoqiuqiu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
