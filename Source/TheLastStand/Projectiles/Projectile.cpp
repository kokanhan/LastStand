// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "../ZoneTrigger/DamageZone.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (isAnimating) 
    {
        TimeElapsed += DeltaTime;

        FVector NewPosition = InitialPosition;
        NewPosition.X += InitialVelocity.X * TimeElapsed;
        NewPosition.Y += InitialVelocity.Y * TimeElapsed;
        NewPosition.Z += InitialVelocity.Z * TimeElapsed + 0.5f * Gravity * FMath::Square(TimeElapsed);

        SetActorLocation(NewPosition);

        float DistanceToTarget = FVector::Dist(NewPosition, TargetPosition);
        float ArrivalThreshold = 10.0f; // Distance threshold to consider as "arrived"

        if (TimeElapsed >= FlyDuration)
        {
            //UE_LOG(LogTemp, Warning, TEXT("Destroyed At = %s"), *NewPosition.ToString());
            castExplosionEffect();
            Destroy();
        }
    }
}

void AProjectile::activeProjectile(int curType, FVector StartLocation, FVector TargetLocation)
{
    this->type = curType;

    InitialPosition = StartLocation;
    TargetPosition = TargetLocation;

    // Calculate launch parameters
    CalculateLaunchParameters();

    float DistanceToTarget = FVector::Dist(StartLocation, TargetLocation);
    //UE_LOG(LogTemp, Warning, TEXT("start = %s end = %s dis = %f"), *StartLocation.ToString(), *TargetLocation.ToString(), DistanceToTarget);

    // Reset time elapsed
    TimeElapsed = 0.f;
    isAnimating = true;
}

void AProjectile::castExplosionEffect()
{
    //if (type == 1) 
    //{
    //    TSubclassOf<ADamageZone> zone = LoadClass<ADamageZone>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_RockExplosion.BP_RockExplosion_C'"));
    //    ADamageZone* cur = GetWorld()->SpawnActor<ADamageZone>(zone, TargetPosition, FRotator(), FActorSpawnParameters());
    //}

    if (type == 11)
    {
        TSubclassOf<ADamageZone> zone = LoadClass<ADamageZone>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_DroneEnd.BP_DroneEnd_C'"));
        ADamageZone* cur = GetWorld()->SpawnActor<ADamageZone>(zone, TargetPosition, FRotator(), FActorSpawnParameters());
    }

    if (type == 19)
    {
        TSubclassOf<ADamageZone> zone = LoadClass<ADamageZone>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_BombExplosion.BP_BombExplosion_C'"));
        ADamageZone* cur = GetWorld()->SpawnActor<ADamageZone>(zone, TargetPosition, FRotator(), FActorSpawnParameters());
    }

    if (type == 16 || type == 20)
    {
        TSubclassOf<ADamageZone> zone = LoadClass<ADamageZone>(nullptr, TEXT("Blueprint'/Game/TopDown/Blueprints/BP_FlameBurning.BP_FlameBurning_C'"));
        ADamageZone* cur = GetWorld()->SpawnActor<ADamageZone>(zone, TargetPosition, FRotator(), FActorSpawnParameters());
    }
}

void AProjectile::CalculateLaunchParameters()
{
    FVector Delta = TargetPosition - InitialPosition;

    // Distance on the X-Y plane
    float Distance = Delta.Size2D(); 
    float HeightDifference = Delta.Z;
    FlyDuration = CalculateFlightTime(0, HeightDifference);

    float Term1 = FMath::Square(LaunchSpeed) - Gravity * HeightDifference;
    float Term2 = FMath::Square(LaunchSpeed) - 2 * Gravity * HeightDifference;
    float UnderRoot = FMath::Sqrt(FMath::Abs(Term1 * Term1 - Gravity * Distance * Distance));

    // Calculate the launch angle
    float Angle1 = FMath::Atan((Term1 + UnderRoot) / (Gravity * Distance));
    float Angle2 = FMath::Atan((Term1 - UnderRoot) / (Gravity * Distance));

    float OutLaunchAngle = FMath::RadiansToDegrees(FMath::Min(Angle1, Angle2));

    float LaunchAngleRad = FMath::DegreesToRadians(OutLaunchAngle);

    InitialVelocity.X = LaunchSpeed * (Distance / (FlyDuration * LaunchSpeed)) * (Delta.X / Distance) * FMath::Cos(LaunchAngleRad);
    InitialVelocity.Y = LaunchSpeed * (Distance / (FlyDuration * LaunchSpeed)) * (Delta.Y / Distance) * FMath::Cos(LaunchAngleRad);
    InitialVelocity.Z = LaunchSpeed * FMath::Sin(LaunchAngleRad);

    //UE_LOG(LogTemp, Warning, TEXT("calDis = %f flyTime = %f vel = %s"), Distance, CalculateFlightTime(0, HeightDifference), *InitialVelocity.ToString());

}

float AProjectile::CalculateFlightTime(float InitialVelocityZ, float HeightDifference)
{
    float a = 0.5f * Gravity;
    float b = InitialVelocityZ;
    float c = -HeightDifference;

    float Discriminant = FMath::Square(b) - 4 * a * c;

    if (Discriminant < 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No valid solution for flight time."));
        return 0.0f;
    }

    float Root1 = (-b + FMath::Sqrt(Discriminant)) / (2 * a);
    float Root2 = (-b - FMath::Sqrt(Discriminant)) / (2 * a);

    // Return the positive root (time cannot be negative)
    return FMath::Max(Root1, Root2);
}

void AProjectile::setSpeed(float targetSpd)
{
    LaunchSpeed = targetSpd;
}