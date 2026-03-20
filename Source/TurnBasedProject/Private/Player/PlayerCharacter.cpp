// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "MyAbilitySystemComponent.h"
#include "MyPlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "UI/HUD_Fight.h"
#include "GameplayTags/TurnBasedGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TurnBasedProject.h"
#include "Enemy/EnemyPawn.h"
#include "GameplayAbilities/RunAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CustomASC->AddLooseGameplayTag(TAG_Mode_TPS);
	if (HUDFight)
	{
		CreateWidget(HUDFight);
	}
	if (CharacterWidget)
	{
		CreateWidget(CharacterWidget);
	}

	PlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CustomASC && !CustomASC->HasMatchingGameplayTag(TAG_Mode_TurnBased))
	{
		CurrentZoom = FMath::FInterpTo(CurrentZoom, TargetZoom, DeltaTime, 15.f);

		CameraBoom->TargetArmLength = CurrentZoom;

		// Normalize
		float Alpha = (CurrentZoom - 100.f) / (400.f - 100.f);

		float ZOffset = FMath::Lerp(0.f, -60.f, Alpha);

		CameraBoom->SocketOffset = FVector(0.f, 0.f, ZOffset);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Run
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &APlayerCharacter::Run);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);

		// Character
		EnhancedInputComponent->BindAction(CharacterAction, ETriggerEvent::Started, this, &APlayerCharacter::Character);

		// Zoom
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &APlayerCharacter::Zoom);
		
	}
	else
	{
		UE_LOG(LogTurnBasedProject, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return CustomASC;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AMyPlayerState* CustomPState = GetPlayerState<AMyPlayerState>())
	{
		CustomASC = Cast<UMyAbilitySystemComponent>(CustomPState->GetAbilitySystemComponent());

		CustomPState->GetAbilitySystemComponent()->InitAbilityActorInfo(CustomPState, this);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (GetController() && CustomASC && !CustomASC->HasMatchingGameplayTag(TAG_Mode_TurnBased))
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
	
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (GetController() && CustomASC && !CustomASC->HasMatchingGameplayTag(TAG_Mode_TurnBased))

	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Run(const FInputActionValue& Value)
{
	if (GetController() && CustomASC)
	{
		CustomASC->TryActivateAbilityByClass(URunAbility::StaticClass());
	}
}

void APlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (GetController() && CustomASC && !CustomASC->HasMatchingGameplayTag(TAG_Mode_TurnBased))
	{
		FVector Start = GetActorLocation();
		FVector End = Start + GetActorForwardVector() * 200;
		float Radius = 80.0f;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		FHitResult OutHit;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		bool bHasHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(),Start,End,Radius,ObjectTypes,
		false,ActorsToIgnore,EDrawDebugTrace::ForDuration,OutHit,true);

		if (bHasHit && PlayerController != nullptr)
		{
			if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(OutHit.GetActor()))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,FString::Printf(TEXT("Hit Actor: %s"), *OutHit.GetActor()->GetName()));
				EnterTurnBasedMode();
			}
		}
	}
}

void APlayerCharacter::Character(const FInputActionValue& Value)
{
	if (CustomASC && !CustomASC->HasMatchingGameplayTag(TAG_Mode_TurnBased))
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0);
		CharacterWidget->AddToViewport();
	}
}

void APlayerCharacter::Zoom(const FInputActionValue& Value)
{
	float ZoomDirection = Value.Get<float>();
	float ZoomSpeed = 100.f;

	if (CustomASC && !CustomASC->HasMatchingGameplayTag(TAG_Mode_TurnBased))
	{
			TargetZoom = FMath::Clamp(TargetZoom + ZoomDirection * ZoomSpeed, 100.f, 400.f);
	}
}

void APlayerCharacter::EnterTurnBasedMode()
{
	CustomASC->AddLooseGameplayTag(TAG_Mode_TurnBased);
	CustomASC->RemoveLooseGameplayTag(TAG_Mode_TPS);

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;
	HUDFight->AddToViewport();
}

void APlayerCharacter::ExitTurnBasedMode()
{
	CustomASC->AddLooseGameplayTag(TAG_Mode_TPS);
	CustomASC->RemoveLooseGameplayTag(TAG_Mode_TurnBased);

	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = false;

	HUDFight->RemoveFromParent();
}