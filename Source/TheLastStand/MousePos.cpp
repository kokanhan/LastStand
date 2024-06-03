// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePos.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMousePos::AMousePos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMousePos::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMousePos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld())
	{
		FVector2D pos;
		FVector2D pos2;
		GetWorld()->GetGameViewport()->GetMousePosition(pos);
		//GetWorld()->GetFirstLocalPlayerFromController()->ViewportClient->GetMousePosition(pos);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(pos2.X, pos2.Y);
		//UE_LOG(LogTemp, Warning, TEXT("x:%f y:%f"), pos2.X, pos2.Y);

		FVector2D mouse_coordinates;
		GEngine->GameViewport->GetMousePosition(mouse_coordinates);//数值都一样 都是屏幕的值

		
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("x:%f y:%f"), mouse_coordinates.X, mouse_coordinates.Y));
	}

}

