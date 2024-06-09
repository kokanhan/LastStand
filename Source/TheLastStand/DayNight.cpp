// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNight.h"
#include "Kismet/GameplayStatics.h"
#include "MyEnemy.h"
#include "GameFramework/Pawn.h"

// Sets default values
ADayNight::ADayNight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//FTimerHandle MemberTimerHandle;
	IsNight = false;
}

// Called when the game starts or when spawned
void ADayNight::BeginPlay()
{
	Super::BeginPlay();


	// Call RepeatingFunction once per second, starting two seconds from now.
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ADayNight::RepeatingFunction, EnemyCrowdSpeed, true, SpawnSpeedDelay);
	
}

// Called every frame
void ADayNight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (LightSource) 
	{
		//
		LightSource->AddActorLocalRotation(FRotator((UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate), 0, 0));
		//UE_LOG(LogTemp, Warning, TEXT("Sun Rotation is %s"), *LightSource->GetActorRotation().ToString());

		// Rotation Y = 9 is night
		if (LightSource->GetActorRotation().Pitch >= 8.f) {
			IsNight = true;
			MoonLight->SetActorHiddenInGame(false);
		}
		else {
			IsNight = false;
			MoonLight->SetActorHiddenInGame(true);
		}
	}
	if (Sun)
	{
		FOutputDeviceNull ar;
		
		
		Sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
	

}

void ADayNight::SpawnEnemy() 
{
	TSubclassOf<AMyEnemy> enemyToSpawn = LoadClass<AMyEnemy>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_MyEnemy.BP_MyEnemy_C'"));
	
	//Area 1
	AMyEnemy* enemySpawnedA1 = GetWorld()->SpawnActor<AMyEnemy>(enemyToSpawn, FVector(FMath::RandRange(- 23890.f, -27190.f), FMath::RandRange(-20860.f, 19065.f), 3290.f), FRotator(), FActorSpawnParameters());
	// min Y -19065.0
	// FVector(random(minX, maxX), random(minY, maxY), Z)
	enemySpawnedA1->SetActorScale3D(FVector(5.0f));
	enemySpawnedA1->SpawnDefaultController();


	//Area 2
	AMyEnemy* enemySpawnedA2 = GetWorld()->SpawnActor<AMyEnemy>(enemyToSpawn, FVector(FMath::RandRange(-23770.f, -22605.f), FMath::RandRange(-26670.f, -24410.f), 3290.f), FRotator(), FActorSpawnParameters());
	enemySpawnedA2->SetActorScale3D(FVector(5.0f));
	enemySpawnedA2->SpawnDefaultController();

	//Area 3
	//(X=-18040.000000,Y=-26335.000000,Z=3050.000000)
	//(X=-16200.000000,Y=-26335.000000,Z=3050.000000)
	//(X=-16200.000000,Y=-23780.000000,Z=3050.000000)
	AMyEnemy* enemySpawnedA3 = GetWorld()->SpawnActor<AMyEnemy>(enemyToSpawn, FVector(FMath::RandRange(-18040.f, -16200.f), FMath::RandRange(-26335.f, 23780.f), 3290.f), FRotator(), FActorSpawnParameters());
	enemySpawnedA3->SetActorScale3D(FVector(5.0f));
	enemySpawnedA3->SpawnDefaultController();

	//Area 4
	// (X=16233.665397,Y=25004.494369,Z=3139.325481)
	// (X=11903.665397,Y=25004.494369,Z=3139.325481)
	AMyEnemy* enemySpawnedA4 = GetWorld()->SpawnActor<AMyEnemy>(enemyToSpawn, FVector(FMath::RandRange(-11903.f, 16233.f), FMath::RandRange(24374.f, 26659.f), 3140.f), FRotator(), FActorSpawnParameters());
	enemySpawnedA4->SetActorScale3D(FVector(5.0f));
	enemySpawnedA4->SpawnDefaultController();

}


void ADayNight::RepeatingFunction()
{
	if (IsNight == true) {

		// Once we've called this function enough times, clear the Timer.
		if (--EnemyTotal <= 0)
		{
			GetWorldTimerManager().ClearTimer(MemberTimerHandle);
			// MemberTimerHandle can now be reused for any other Timer.
		}
		// Do something here...
		SpawnEnemy();
		

	}
	
}

