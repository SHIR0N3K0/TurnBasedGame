// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "MyPlayerState.generated.h"

class UPlayerAttributeSet;
class UMyAbilitySystemComponent;
class UWalkAbility;
class URunAbility;
/**
 * 
 */
UCLASS()
class TURNBASEDPROJECT_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (allowPrivateAccess = "true"))
	UMyAbilitySystemComponent* CustomASC;

	public:
	AMyPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerAttributeSet* PlayerAttributSet;
};
