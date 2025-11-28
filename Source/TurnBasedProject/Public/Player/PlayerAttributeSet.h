// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class TURNBASEDPROJECT_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPlayerAttributeSet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health = 100;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_HealthMax)
	FGameplayAttributeData HealthMax = 100;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, HealthMax);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_HealthMax)
	FGameplayAttributeData AttackPoint = 5;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, AttackPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_HealthMax)
	FGameplayAttributeData AttackPointMax = 5;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, AttackPointMax);

protected : 
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);

	UFUNCTION()
	virtual void OnRep_AttackPoint(const FGameplayAttributeData& OldAttackPoint);

	UFUNCTION()
	virtual void OnRep_AttackPointMax(const FGameplayAttributeData& OldAttackPointMax);
	
};
