// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "PlayerAttributeSet.h"
#include "MyAbilitySystemComponent.h"

AMyPlayerState::AMyPlayerState()
{
	CustomASC = CreateDefaultSubobject<UMyAbilitySystemComponent>("CustomASC");

	PlayerAttributSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributSet"));
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return CustomASC;
}
