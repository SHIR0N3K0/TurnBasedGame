// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/RunAbility.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void URunAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		ACharacter* CharacterREF = Cast<ACharacter>(GetAvatarActorFromActorInfo());

		CharacterREF->GetCharacterMovement()->MaxWalkSpeed += AddRunSpeed;
	}
}
