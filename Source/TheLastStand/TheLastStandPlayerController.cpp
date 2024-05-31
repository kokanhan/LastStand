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
#include "MyPlayerState.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
//#include "TheLastStandCharacter.cpp"


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
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATheLastStandPlayerController::ZoomView);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	//set up axis binds for zoom in/out function
	
}

void ATheLastStandPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATheLastStandPlayerController::OnSetDestinationTriggered()
{
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
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;

	// test see if get ATheLastStandCharacter or not
	ATheLastStandCharacter* LastStandCharacter = Cast<ATheLastStandCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//UE_LOG(LogTemp, Warning, TEXT("sha?: %f"), LastStandCharacter->gg);
}

// Triggered every frame when the input is held down
void ATheLastStandPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATheLastStandPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATheLastStandPlayerController::OnESCClicked() 
{
	if (!isOnSynLayout)
	{
		Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->layout->showSynListLayout();
	}
	else 
	{
		Cast<AMyPlayerState>(GetPawn()->GetPlayerState())->layout->hideSynListLayout();
	}

	isOnSynLayout = !isOnSynLayout;
}


void ATheLastStandPlayerController::ZoomView(const FInputActionValue& Value)
{
	

	class ATheLastStandCharacter* LastStandCharacter = Cast<ATheLastStandCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	float ZoomAxisVal = Value.Get<float>();
	float offset = ZoomAxisVal * ZoomStep * UGameplayStatics::GetWorldDeltaSeconds(this);
	float armLength = LastStandCharacter->CameraBoom->TargetArmLength + offset;
	LastStandCharacter->CameraBoom->TargetArmLength = FMath::Clamp(armLength, 2500.0f, 20000.0f);//改成可控制最大和最小值
	UE_LOG(LogTemp, Warning, TEXT("sha?: %f"), LastStandCharacter->CameraBoom->TargetArmLength);

}
