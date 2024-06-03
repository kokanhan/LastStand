// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
	//super class version you are extending the functionality whereas without you are completely replacing the functionality.
	Super::BeginPlay();

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);
	//MoveToActor(PlayerPawn);
	//if (AIBehavior != nullptr)
	//{
	//	
	//	/*RunBehaviorTree(AIBehavior);
	//	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerBasement"), GetPawn()->GetActorLocation());*/
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("weism buchuxian"));
	//}

	UE_LOG(LogTemp, Warning, TEXT("kaishi"));
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn);
	MoveToActor(PlayerPawn, DetectionRange);

	FVector dir = GetPawn()->GetActorLocation() - PlayerPawn->GetActorLocation();
	dir.Normalize();
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PlayerPawn->GetActorLocation());
	
	
	
	//if (LineOfSightTo(PlayerPawn))
	//{
	//	SetFocus(PlayerPawn);
	//	MoveToActor(PlayerPawn, DetectionRange);
	//}

	//else
	//{
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();//暂时stop 应该朝山顶爬
	//}


}