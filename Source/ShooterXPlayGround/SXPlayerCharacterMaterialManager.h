// SXPlayerCharacterMaterialManager.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SXPlayerCharacterMaterialManager.generated.h"

/**
 *
 */
UCLASS(config = PlayerCharacterMeshMaterialPaths)
class SHOOTERXPLAYGROUND_API USXPlayerCharacterMaterialManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(config)
	TArray<FSoftObjectPath> PlayerCharacterMeshMaterialPaths;

};
