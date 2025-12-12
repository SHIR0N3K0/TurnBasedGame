// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AJRPGController;
class ATPSController;
/**
 * 
 */
UCLASS()
class TURNBASEDPROJECT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	ATPSController* TPSController;

	UPROPERTY()
	AJRPGController* JRPGController;
	
	UFUNCTION()
	void SetController();

	template<typename ControllerClass>
	void SwitchToController();
};
