// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Player/PlayerAttributeSet.h"
#include "MyAbilitySystemComponent.h"

AMyPlayerState::AMyPlayerState()
{
	CustomASC = CreateDefaultSubobject<UMyAbilitySystemComponent>("CustomASC");
	CustomASC->SetIsReplicated(true);
	CustomASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	SetNetUpdateFrequency(100);

	PlayerAttributSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributSet"));
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return CustomASC;
}
