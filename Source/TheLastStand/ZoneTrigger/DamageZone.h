// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageZone.generated.h"

UCLASS()
class THELASTSTAND_API ADamageZone : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> customValue;
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> objectList;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> warningArea;
	UPROPERTY(BlueprintReadOnly)
	float hp;
	UPROPERTY(BlueprintReadOnly)
	float curHP;
private:
	TArray<float> cdList;
	
	float cd;
	float dmg;
	float curTime;

public:	
	// Sets default values for this actor's properties
	ADamageZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void objectEnter(AActor* cur);
	UFUNCTION(BlueprintCallable)
	void objectExit(AActor* cur);
	UFUNCTION(BlueprintCallable)
	void setProperty(float maxHP, float time, float damage, float cooldown);
	UFUNCTION(BlueprintCallable)
	AActor* getClosestEnemy(int index);
private:
	void applyDMG(AActor* cur);
};
