// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PlayerCharacter.generated.h"

class UMyAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UHUD_Fight;
class ACustomPlayerController;
struct FInputActionValue;

UCLASS()
class TURNBASEDPROJECT_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMyAbilitySystemComponent* CustomASC;


public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="UI")
	UHUD_Fight* HUDFight;
	
	UPROPERTY(EditAnywhere, Category="Controller")
	ACustomPlayerController* PlayerController;

	/** MoveInput Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** LookInput Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AttackAction;
	
	//----------------------------------------------InputEvent-----------------------------------------------------
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Run(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void PossessedBy(AController* NewController);

	UFUNCTION()
	void EnterTurnBasedMode();
	UFUNCTION()
	void ExitTurnBasedMode();

};
