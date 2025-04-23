// SXTorch.cpp


#include "Gimmick/SXTorch.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASXTorch::ASXTorch()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SetRootComponent(BoxComponent);

    BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
    BodyStaticMeshComponent->SetupAttachment(GetRootComponent());
    BodyStaticMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyStaticMesh(TEXT("/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500"));
    // 경로 정보가 런타임 중에는 변경되지 않으므로, static 키워드 사용.
    if (true == BodyStaticMesh.Succeeded())
    {
        BodyStaticMeshComponent->SetStaticMesh(BodyStaticMesh.Object);
    }

    PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
    PointLightComponent->SetupAttachment(GetRootComponent());
    PointLightComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(GetRootComponent());
    ParticleSystemComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleTemplate(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
    if (true == ParticleTemplate.Succeeded())
    {
        ParticleSystemComponent->SetTemplate(ParticleTemplate.Object);
    }
}
