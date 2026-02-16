// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Player/PlayerAttributeSet.h"
#include "MyAbilitySystemComponent.h"
#include "GameplayAbilities/RunAbility.h"


AMyPlayerState::AMyPlayerState()
{
	CustomASC = CreateDefaultSubobject<UMyAbilitySystemComponent>("CustomASC");
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return CustomASC;
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && CustomASC)
	{
		GiveDefaultAbilities();
	}
}

void AMyPlayerState::GiveDefaultAbilities()
{
	if (!RunAbility) return;

	CustomASC->GiveAbility(
		FGameplayAbilitySpec(RunAbility, 1, 0)
	);
}

