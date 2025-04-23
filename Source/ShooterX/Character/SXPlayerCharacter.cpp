// SXPlayerCharacter.cpp


#include "Character/SXPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/SXInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

ASXPlayerCharacter::ASXPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
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
}

void ASXPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetViewMode(EViewMode::BackView);
}

void ASXPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == true)
	{
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
	}
}

void ASXPlayerCharacter::InputMove(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
	{ // Switch-Case 구문 내에서 Scope를 지정하면 해당 Scope 내에서 변수 선언이 가능해짐.
		const FRotator ControlRotation = GetController()->GetControlRotation();
		const FRotator ControlRotationYaw(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, MovementVector.X);
		AddMovementInput(RightVector, MovementVector.Y);

		break;
	}
	case EViewMode::None:
	case EViewMode::End:
	default:
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
		break;
	}
}

void ASXPlayerCharacter::InputLook(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
		break;
	case EViewMode::None:
	case EViewMode::End:
	default:
		break;
	}
}

void ASXPlayerCharacter::SetViewMode(EViewMode InViewMode)
{
	if (CurrentViewMode == InViewMode)
	{
		return;
	}

	CurrentViewMode = InViewMode;

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		SpringArmComponent->TargetArmLength = 400.f;
		SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);

		SpringArmComponent->bUsePawnControlRotation = true;

		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritYaw = true;
		SpringArmComponent->bInheritRoll = false;

		SpringArmComponent->bDoCollisionTest = true;

		GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;

		break;
	case EViewMode::None:
	case EViewMode::End:
	default:
		break;
	}
}
