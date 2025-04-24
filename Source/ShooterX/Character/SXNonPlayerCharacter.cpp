// SXNonPlayerCharacter.cpp


#include "Character/SXNonPlayerCharacter.h"

#include "Controller/SXAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASXNonPlayerCharacter::ASXNonPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ASXAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASXNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (false == IsPlayerControlled())
	{
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
}
