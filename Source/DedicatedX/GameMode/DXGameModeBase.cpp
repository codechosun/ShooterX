// DXGameModeBase.cpp


#include "GameMode/DXGameModeBase.h"

#include "Controller/DXPlayerController.h"

void ADXGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ADXPlayerController* NewPlayerController = Cast<ADXPlayerController>(NewPlayer);
	if (IsValid(NewPlayerController) == true)
	{
		AlivePlayerControllers.Add(NewPlayerController);

		NewPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
	}
}

void ADXGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	ADXPlayerController* ExitingPlayerController = Cast<ADXPlayerController>(Exiting);
	if (IsValid(ExitingPlayerController) == true && AlivePlayerControllers.Find(ExitingPlayerController) != INDEX_NONE)
	{
		AlivePlayerControllers.Remove(ExitingPlayerController);
		DeadPlayerControllers.Add(ExitingPlayerController);
	}
}
