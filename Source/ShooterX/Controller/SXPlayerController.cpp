// SXPlayerController.cpp


#include "Controller/SXPlayerController.h"

ASXPlayerController::ASXPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}
