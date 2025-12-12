// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void ATPSController::BeginPlay()
{
	Super::BeginPlay();
}

void ATPSController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}
