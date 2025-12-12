// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JRPGController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AJRPGController::BeginPlay()
{
	Super::BeginPlay();
}

void AJRPGController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				//Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}
