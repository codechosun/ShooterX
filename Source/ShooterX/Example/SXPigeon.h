// SXPigeon.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Example/SXFlyable.h" 
#include "SXPigeon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERX_API USXPigeon
	: public UObject
	, public ISXFlyable
{
	GENERATED_BODY()

public:
	USXPigeon();

	virtual void Fly() override;

private:
	UPROPERTY()
	FString Name;

};
