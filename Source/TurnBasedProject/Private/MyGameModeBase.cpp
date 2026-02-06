// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Player/CustomPlayerController.h"

void AMyGameModeBase::SetController()
{
	APlayerController* CurrentController = GetWorld()->GetFirstPlayerController();
    
	if (!CurrentController)
	{
		return;
	}
	
}