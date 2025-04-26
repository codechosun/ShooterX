// CXGameModeBase.cpp


#include "Game/CXGameModeBase.h"

#include "CXGameStateBase.h"

void ACXGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ACXGameStateBase* CXGameStateBase = GetGameState<ACXGameStateBase>();
	if (IsValid(CXGameStateBase) == true)
	{
		CXGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXXX"));
	}
}