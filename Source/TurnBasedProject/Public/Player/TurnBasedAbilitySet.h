// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TurnBasedAbilitySet.generated.h"

/**
 * 
 */

class UGameplayAbility;

UCLASS()
class TURNBASEDPROJECT_API UTurnBasedAbilitySet : public UObject
{
	GENERATED_BODY()

public:

	// All the abilities in this set
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;
};
