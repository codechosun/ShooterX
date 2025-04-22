// SXTorch.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SXTorch.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UPointLightComponent;
class UParticleSystemComponent;

UCLASS()
class SHOOTERX_API ASXTorch : public AActor
{
    GENERATED_BODY()

public:
    ASXTorch();

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UBoxComponent> BoxComponent;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> BodyStaticMeshComponent;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UPointLightComponent> PointLightComponent;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

};

