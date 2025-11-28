// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/SkeletalMesh.h"
#include "EnemyStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	FName Name = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	TObjectPtr<USkeletalMesh> Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float HealthMax = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float Attack = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float AttackMax = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float Defense = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float DefenseMax = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float Speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnBased")
	float SpeedMax = 100.0f;
};
