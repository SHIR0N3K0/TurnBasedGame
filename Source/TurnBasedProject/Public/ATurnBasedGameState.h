// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ATurnBasedGameState.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDPROJECT_API AATurnBasedGameState : public AGameStateBase
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TargetActorClass;

	protected:

	virtual void BeginPlay() override;

	void SpawnPreview();
};
