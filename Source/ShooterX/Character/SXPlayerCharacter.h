// SXPlayerCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "Character/SXCharacterBase.h"
#include "InputActionValue.h"
#include "SXPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USXInputConfig;
class UInputMappingContext;
struct FStreamableHandle;
class UCameraShakeBase;

/**
 *
 */
UCLASS()
class SHOOTERX_API ASXPlayerCharacter : public ASXCharacterBase
{
	GENERATED_BODY()

#pragma region Override ACharacter

public:
	ASXPlayerCharacter();

	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;

#pragma endregion

#pragma region Input

private:
	void InputMove(const FInputActionValue& InValue);

	void InputLook(const FInputActionValue& InValue);

	void InputAttackMelee(const FInputActionValue& InValue);

	void InputAttackRanged(const FInputActionValue& InValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USXInputConfig> PlayerCharacterInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> PlayerCharacterInputMappingContext;

#pragma endregion

#pragma region MeshMaterial

protected:
	FSoftObjectPath CurrentPlayerCharacterMeshMaterialPath01 = FSoftObjectPath();

	FSoftObjectPath CurrentPlayerCharacterMeshMaterialPath02 = FSoftObjectPath();

	TSharedPtr<FStreamableHandle> AssetStreamableHandle = nullptr;

#pragma endregion

#pragma region Effect

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> AttackRangedCameraShake;

#pragma endregion 

};
