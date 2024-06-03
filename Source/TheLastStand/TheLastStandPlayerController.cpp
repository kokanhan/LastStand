// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLastStandPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TheLastStandCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "DestroyableObject.h"
#include "MyPlayerState.h"
#include "MyGameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATheLastStandPlayerController::ATheLastStandPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATheLastStandPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ATheLastStandPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATheLastStandPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATheLastStandPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATheLastStandPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATheLastStandPlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(ESC, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::OnESCClicked);
		//EnhancedInputComponent->BindAction(rightButton, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::pickUp);

		EnhancedInputComponent->BindAction(num1Button, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::useItem, 0);
		EnhancedInputComponent->BindAction(num2Button, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::useItem, 1);
		EnhancedInputComponent->BindAction(num3Button, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::useItem, 2);
		EnhancedInputComponent->BindAction(num4Button, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::useItem, 3);
		EnhancedInputComponent->BindAction(num5Button, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::useItem, 4);
		EnhancedInputComponent->BindAction(num6Button, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::useItem, 5);
		EnhancedInputComponent->BindAction(mouseWheelUp, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::setCurBuildingPresetRot, true);
		EnhancedInputComponent->BindAction(mouseWheelDown, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::setCurBuildingPresetRot, false);
		EnhancedInputComponent->BindAction(QButton, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::shoot);

		EnhancedInputComponent->BindAction(FButton, ETriggerEvent::Completed, this, &ATheLastStandPlayerController::collectItem);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::ZoomView);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATheLastStandPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATheLastStandPlayerController::OnSetDestinationTriggered()
{
	if (Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding)
	{
		return;
	}

	if (isOnInventoryLayout) 
	{
		return;
	}

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATheLastStandPlayerController::OnSetDestinationReleased()
{
	if (Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding)
	{
		Cast<AMyGameStateBase>(GetWorld()->GetGameState())->playerStartBuild(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()));
		Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding = false;

		return;
	}

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATheLastStandPlayerController::OnTouchTriggered()
{
	if (Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding)
	{
		return;
	}

	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATheLastStandPlayerController::OnTouchReleased()
{
	if (Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding)
	{
		return;
	}

	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATheLastStandPlayerController::OnESCClicked() 
{
	isOnInventoryLayout = !isOnInventoryLayout;
	Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->layout->showLayout(isOnInventoryLayout);
	Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->layout->showInventoryLayout(isOnInventoryLayout);
	//Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->layout->showSynListLayout(isOnInventoryLayout);
	Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->layout->showPlayerStatusLayout(isOnInventoryLayout);
}

void ATheLastStandPlayerController::pickUp()
{
	if (Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding)
	{
		Cast<AMyGameStateBase>(GetWorld()->GetGameState())->playerStopBuild(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()));
		Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding = false;

		return;
	}

	FHitResult hit(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);

	if (Cast<ADestroyableObject>(hit.GetActor()) != NULL)
	{
		ADestroyableObject* cur = Cast<ADestroyableObject>(hit.GetActor());
		cur->dropNow(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()));
	}
}


void ATheLastStandPlayerController::useItem(int cur)
{
	//if (true) 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%d"), cur);

	//	return;
	//}

	if (Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->equippedItems[cur].id == -1)
	{	
		return;
	}

	if (Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->items[Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->equippedItems[cur].id].count <= 0)
	{
		return;
	}

	if (Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->equippedItems[cur].type == 1)
	{
		FHitResult hit(ForceInit);
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);
		Cast<AMyGameStateBase>(GetWorld()->GetGameState())->playerUseItem(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()), Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->equippedItems[cur].id, GetPawn()->GetActorLocation(), hit.Location);

		FVector dir = hit.Location - GetPawn()->GetActorLocation();
		dir.Normalize();

		GetPawn()->SetActorRotation(dir.ToOrientationRotator());
	}
	else if (Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->equippedItems[cur].type == 2)
	{
		buildItem(cur);
	}
}

void ATheLastStandPlayerController::buildItem(int cur) 
{
	if (isOnInventoryLayout)
	{
		return;
	}

	FHitResult hit(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);
	Cast<AMyGameStateBase>(GetWorld()->GetGameState())->playerTryBuild(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()), Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->equippedItems[cur].id, hit.Location);

	Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding = true;
}

void ATheLastStandPlayerController::setCurBuildingPresetPos()
{
	FHitResult hit(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);
	Cast<AMyGameStateBase>(GetWorld()->GetGameState())->setBuidingPresetPos(hit.Location);
}


void ATheLastStandPlayerController::setCurBuildingPresetRot(bool isUp)
{
	Cast<AMyGameStateBase>(GetWorld()->GetGameState())->setBuildingPresetRot(isUp, FApp::GetDeltaTime());
}

void ATheLastStandPlayerController::collectItem()
{
	float minDis = 8753;
	float minIndex = -1;

	for (int i = 0; i < Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->collectableObjects.Num(); i += 1) 
	{
		float curDis = FVector::Dist(GetPawn()->GetActorLocation(), Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->collectableObjects[i]->GetActorLocation());

		if (curDis < minDis)
		{
			minDis = curDis;
			minIndex = i;
		}
	}

	if (minIndex != -1)
	{
		ADestroyableObject* cur = Cast<ADestroyableObject>(Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->collectableObjects[minIndex]);
		Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->collectableObjects.RemoveAt(minIndex);

		if (cur == NULL) 
		{
			UE_LOG(LogTemp, Error, TEXT("Object going to collect have no tag: Collectable"));

			return;
		}

		cur->dropNow(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()));
		cur->Destroy();
	}
}


// wuyule
void ATheLastStandPlayerController::ZoomView(const FInputActionValue& Value)
{
	if (Cast<ATheLastStandCharacter>(GetPawn())->isPlacingBuilding || isOnInventoryLayout) 
	{
		return;
	}

	ATheLastStandCharacter* LastStandCharacter = Cast<ATheLastStandCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	float ZoomAxisVal = Value.Get<float>();
	float offset = ZoomAxisVal * ZoomStep * UGameplayStatics::GetWorldDeltaSeconds(this);
	float armLength = LastStandCharacter->CameraBoom->TargetArmLength + offset;
	LastStandCharacter->CameraBoom->TargetArmLength = FMath::Clamp(armLength, 2500.0f, 20000.0f);//改成可控制最大和最小值
	UE_LOG(LogTemp, Warning, TEXT("sha?: %f"), LastStandCharacter->CameraBoom->TargetArmLength);

}

void ATheLastStandPlayerController::shoot() 
{
	FHitResult hit(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);

	FVector targetPos;

	if (hit.GetActor() != NULL && hit.GetActor()->ActorHasTag("Monster")) 
	{
		targetPos = hit.GetActor()->GetActorLocation();
	}
	else 
	{
		targetPos = FVector(hit.Location.X, hit.Location.Y, GetPawn()->GetActorLocation().Z);
	}

	Cast<AMyGameStateBase>(GetWorld()->GetGameState())->shootAtPos(Cast<AMyPlayerState>(GetPawn()->GetPlayerState()), hit.Location);

	FVector dir = hit.Location - GetPawn()->GetActorLocation();
	dir.Normalize();

	GetPawn()->SetActorRotation(dir.ToOrientationRotator());
}

