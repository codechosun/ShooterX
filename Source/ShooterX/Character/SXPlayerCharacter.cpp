// SXPlayerCharacter.cpp


#include "Character/SXPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/SXInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/SXAnimInstance.h"
#include "ShooterXPlayGround/SXPlayerCharacterMaterialManager.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Item/SXWeapon.h"

ASXPlayerCharacter::ASXPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bDoCollisionTest = true;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 25.f, 25.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

void ASXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (IsValid(PlayerController) == true)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (IsValid(Subsystem) == true)
		{
			Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
		}
	}

	const USXPlayerCharacterMaterialManager* CDO = GetDefault<USXPlayerCharacterMaterialManager>();
	int32 RandomIndex = FMath::RandRange(0, (CDO->PlayerCharacterMeshMaterialPaths.Num() / 2) - 1);
	CurrentPlayerCharacterMeshMaterialPath01 = CDO->PlayerCharacterMeshMaterialPaths[RandomIndex];
	CurrentPlayerCharacterMeshMaterialPath02 = CDO->PlayerCharacterMeshMaterialPaths[RandomIndex + 1];
	AssetStreamableHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		{ CurrentPlayerCharacterMeshMaterialPath01, CurrentPlayerCharacterMeshMaterialPath02 },
		FStreamableDelegate::CreateLambda([this]() -> void
			{
				AssetStreamableHandle->ReleaseHandle();
				TSoftObjectPtr<UMaterialInstance> LoadedMaterialInstance01(CurrentPlayerCharacterMeshMaterialPath01);
				TSoftObjectPtr<UMaterialInstance> LoadedMaterialInstance02(CurrentPlayerCharacterMeshMaterialPath02);
				if (LoadedMaterialInstance01.IsValid() == true && LoadedMaterialInstance02.IsValid() == true)
				{
					GetMesh()->SetMaterial(1, LoadedMaterialInstance01.Get());
					GetMesh()->SetMaterial(0, LoadedMaterialInstance02.Get());
				}
			}
		)
	);
}

void ASXPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == true)
	{
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->AttackMelee, ETriggerEvent::Started, this, &ThisClass::InputAttackMelee);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->AttackRanged, ETriggerEvent::Started, this, &ThisClass::InputAttackRanged);
	}
}

void ASXPlayerCharacter::InputMove(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	const FRotator ControlRotation = GetController()->GetControlRotation();
	const FRotator ControlRotationYaw(0.f, ControlRotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, MovementVector.X);
	AddMovementInput(RightVector, MovementVector.Y);
}

void ASXPlayerCharacter::InputLook(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ASXPlayerCharacter::InputAttackMelee(const FInputActionValue& InValue)
{
	if (GetCharacterMovement()->IsFalling() == true)
	{
		return;
	}

	if (0 == CurrentComboCount)
	{
		BeginAttack();
	}
	else
	{
		ensure(FMath::IsWithinInclusive<int32>(CurrentComboCount, 1, MaxComboCount));
		bIsAttackKeyPressed = true;
	}
}

void ASXPlayerCharacter::InputAttackRanged(const FInputActionValue& InValue)
{
	if (0.f < GetCharacterMovement()->Velocity.Size())
	{
		return;
	}

	if (IsValid(CurrentWeapon) == false)
	{
		return;
	}

	if (IsValid(GetCurrentWeaponAttackAnimMontage()) == false)
	{
		return;
	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (IsValid(AnimInstance) == true)
	{
		if (AnimInstance->Montage_IsPlaying(GetCurrentWeaponAttackAnimMontage()) == false)
		{
			AnimInstance->Montage_Play(GetCurrentWeaponAttackAnimMontage());
		}
	}

	APlayerController* OwnerPlayerController = Cast<APlayerController>(GetController());
	if (IsValid(AttackRangedCameraShake) == true && IsValid(OwnerPlayerController) == true)
	{
		OwnerPlayerController->ClientStartCameraShake(AttackRangedCameraShake);
	}
}

