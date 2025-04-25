// SXWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SXWeapon.generated.h"

class ASXPlayerCharacter;
class USXPickupComponent;
class UAnimMontage;

UCLASS()
class SHOOTERX_API ASXWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASXWeapon();

	USXPickupComponent* GetPickupComponent() const { return PickupComponent; }

	UAnimMontage* GetAttackMontage() const { return AttackMontage; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnPickUp(ASXPlayerCharacter* InPickUpCharacter);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USXPickupComponent> PickupComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage;

};
