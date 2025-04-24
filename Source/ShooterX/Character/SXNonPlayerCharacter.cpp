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
