// DXGameModeBase.h

#pragma once

#include "GameFramework/GameModeBase.h"
#include "DXGameModeBase.generated.h"

class ADXPlayerController;

/**
 *
 */
UCLASS()
class DEDICATEDX_API ADXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ADXPlayerController>> AlivePlayerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ADXPlayerController>> DeadPlayerControllers;

};
