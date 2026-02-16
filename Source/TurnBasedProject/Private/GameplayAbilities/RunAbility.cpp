// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/RunAbility.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/TurnBasedGameplayTags.h"

URunAbility::URunAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(TAG_Mode_TurnBased);

	bRetriggerInstancedAbility = true;
}

void URunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		return;

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character) return;

	if (bRunning == false)
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 500.f;
		bRunning = true;
	}
	else
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = 300.f;
		bRunning = false;
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
