// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Projectiles/Projectile.h"
#include "ZoneTrigger/DamageZone.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheLastStandCharacter.h"

void AMyGameStateBase::initSynthesisList() 
{
	TArray<FItem> electricWeb;
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(13, 1));
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(0, 2));
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(1, 4));
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(2, 4));
	synthesisList.Add(electricWeb);

	TArray<FItem> throwRockMachine;
	throwRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(14, 1));
	throwRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(0, 20));
	throwRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(9, 4));
	throwRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(3, 10));
	synthesisList.Add(throwRockMachine);

	TArray<FItem> autoThrowRockMachine;
	autoThrowRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(15, 1));
	autoThrowRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(14, 1));
	autoThrowRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(2, 8));
	autoThrowRockMachine.Add(UMyBlueprintFunctionLibrary::itemInit(9, 25));
	synthesisList.Add(autoThrowRockMachine);

	TArray<FItem> fireBomb;
	fireBomb.Add(UMyBlueprintFunctionLibrary::itemInit(16, 3));
	fireBomb.Add(UMyBlueprintFunctionLibrary::itemInit(8, 2));
	fireBomb.Add(UMyBlueprintFunctionLibrary::itemInit(4, 5));
	synthesisList.Add(fireBomb);

	TArray<FItem> fireBomb2;
	fireBomb2.Add(UMyBlueprintFunctionLibrary::itemInit(16, 3));
	fireBomb2.Add(UMyBlueprintFunctionLibrary::itemInit(5, 1));
	fireBomb2.Add(UMyBlueprintFunctionLibrary::itemInit(4, 1));
	synthesisList.Add(fireBomb2);

	TArray<FItem> bigRock;
	bigRock.Add(UMyBlueprintFunctionLibrary::itemInit(17, 1));
	bigRock.Add(UMyBlueprintFunctionLibrary::itemInit(10, 3));
	synthesisList.Add(bigRock);

	TArray<FItem> bullet;
	bullet.Add(UMyBlueprintFunctionLibrary::itemInit(18, 20));
	bullet.Add(UMyBlueprintFunctionLibrary::itemInit(8, 2));
	bullet.Add(UMyBlueprintFunctionLibrary::itemInit(1, 5));
	synthesisList.Add(bullet);

	TArray<FItem> bomb;
	bomb.Add(UMyBlueprintFunctionLibrary::itemInit(19, 3));
	bomb.Add(UMyBlueprintFunctionLibrary::itemInit(8, 5));
	bomb.Add(UMyBlueprintFunctionLibrary::itemInit(9, 1));
	synthesisList.Add(bomb);

	TArray<FItem> poisonBomb;
	poisonBomb.Add(UMyBlueprintFunctionLibrary::itemInit(20, 3));
	poisonBomb.Add(UMyBlueprintFunctionLibrary::itemInit(8, 3));
	poisonBomb.Add(UMyBlueprintFunctionLibrary::itemInit(23, 30));
	poisonBomb.Add(UMyBlueprintFunctionLibrary::itemInit(4, 2));
	synthesisList.Add(poisonBomb);

	TArray<FItem> fence;
	fence.Add(UMyBlueprintFunctionLibrary::itemInit(21, 5));
	fence.Add(UMyBlueprintFunctionLibrary::itemInit(3, 3));
	fence.Add(UMyBlueprintFunctionLibrary::itemInit(0, 10));
	synthesisList.Add(fence);

	TArray<FItem> backFierce;
	backFierce.Add(UMyBlueprintFunctionLibrary::itemInit(22, 3));
	backFierce.Add(UMyBlueprintFunctionLibrary::itemInit(6, 5));
	backFierce.Add(UMyBlueprintFunctionLibrary::itemInit(1, 25));
	synthesisList.Add(backFierce);

	TArray<FItem> smallIron;
	smallIron.Add(UMyBlueprintFunctionLibrary::itemInit(1, 10));
	smallIron.Add(UMyBlueprintFunctionLibrary::itemInit(9, 1));
	synthesisList.Add(smallIron);

	TArray<FItem> iron;
	iron.Add(UMyBlueprintFunctionLibrary::itemInit(9, 1));
	iron.Add(UMyBlueprintFunctionLibrary::itemInit(1, 15));
	synthesisList.Add(iron);
}

void AMyGameStateBase::playerUseItem(AMyPlayerState* playState, int type, FVector startPos, FVector endPos)
{
	if (type == 1)
	{
		TSubclassOf<AProjectile> rock = LoadClass<AProjectile>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_ProjectileRock.BP_ProjectileRock_C'"));
		AProjectile* cur = GetWorld()->SpawnActor<AProjectile>(rock, startPos, FRotator(), FActorSpawnParameters());
		cur->activeProjectile(type, startPos, endPos);
	}

	if (type == 2)
	{
		if (Cast<ATheLastStandCharacter>(playState->GetPawn())->shootingCD <= 0) 
		{
			TSubclassOf<ADamageZone> bullet = LoadClass<ADamageZone>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_Bullet.BP_Bullet_C'"));
			ADamageZone* cur = GetWorld()->SpawnActor<ADamageZone>(bullet, startPos, FRotator(), FActorSpawnParameters());

			FVector velocity = (endPos - startPos);
			velocity.Normalize();

			cur->customValue.Add(FVector(velocity.X, velocity.Y, 0) * 50);

			Cast<ATheLastStandCharacter>(playState->GetPawn())->shootingCD += 0.05f;
		}
	}
}