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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SXTorch", Meta = (AllowPrivateAccess))
    TObjectPtr<UBoxComponent> BoxComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SXTorch", Meta = (AllowPrivateAccess))
    TObjectPtr<UStaticMeshComponent> BodyStaticMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SXTorch", Meta = (AllowPrivateAccess))
    TObjectPtr<UPointLightComponent> PointLightComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SXTorch", Meta = (AllowPrivateAccess))
    TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "SXTorch", meta=(AllowPrivateAccess))
    int32 ID;

};

