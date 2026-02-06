// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTags/TurnBasedGameplayTags.h"
#include "AddTurnBasedTag.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDPROJECT_API UAddTurnBasedTag : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UAddTurnBasedTag()
	{
		DurationPolicy = EGameplayEffectDurationType::Infinite	; // Or Infinite if you want it persistent

		// Add the Mode.TurnBased tag to the Granted Tags
		FGameplayTagContainer Tags;
		Tags.AddTag(TAG_Mode_TurnBased);
	}
};
