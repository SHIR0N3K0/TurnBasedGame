// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RunAbility.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASEDPROJECT_API URunAbility : public UGameplayAbility
{
	GENERATED_BODY()

	URunAbility();
	
	public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Abilities")
	bool bRunning = false;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
