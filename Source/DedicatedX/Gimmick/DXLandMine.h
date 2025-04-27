// DXLandMine.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DXLandMine.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class DEDICATEDX_API ADXLandMine : public AActor
{
	GENERATED_BODY()

public:
	ADXLandMine();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> Mesh;

};
