// Fill out your copyright notice in the Description page of Project Settings.


#include "ATurnBasedGameState.h"

#include "K2Node_SpawnActorFromClass.h"
#include "Nodes/InterchangeBaseNode.h"

void AATurnBasedGameState::BeginPlay()
{
	Super::BeginPlay();

	SpawnPreview();
}

void AATurnBasedGameState::SpawnPreview()
{
	if (!TargetActor)
	{
		TargetActor = GetWorld()->SpawnActor<AActor>(TargetActorClass);
		
		TargetActor->SetActorLocation(FVector(0, 0, -10000));
	}
}
