// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Player/JRPGController.h"
#include "Player/TPSController.h"

void AMyGameModeBase::SetController()
{
	APlayerController* CurrentController = GetWorld()->GetFirstPlayerController();
    
	if (!CurrentController)
	{
		return;
	}

	// Check if current controller is TPSController
	if (Cast<ATPSController>(CurrentController))
	{
		// Switch to JRPGController
		SwitchToController<AJRPGController>();
	}
	else if (Cast<AJRPGController>(CurrentController))
	{
		// Switch to TPSController
		SwitchToController<ATPSController>();
	}
}

template<typename ControllerClass>
void AMyGameModeBase::SwitchToController()
{
	APlayerController* OldController = GetWorld()->GetFirstPlayerController();
	if (!OldController)
	{
		return;
	}

	APawn* PlayerPawn = OldController->GetPawn();
    
	// Spawn new controller
	ControllerClass* NewController = GetWorld()->SpawnActor<ControllerClass>();
	if (!NewController)
	{
		return;
	}

	// Possess the pawn with new controller
	NewController->Possess(PlayerPawn);
    
	// Destroy old controller
	OldController->Destroy();
}