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

UENUM(BlueprintType)
enum class EViewMode : uint8
{
	None,
	BackView,
	End
};

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

	virtual void PossessedBy(AController* NewController) override;

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USXInputConfig> PlayerCharacterInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> PlayerCharacterInputMappingContext;

#pragma endregion	

#pragma region ViewMode

public:
	void SetViewMode(EViewMode InViewMode);

protected:
	EViewMode CurrentViewMode = EViewMode::None;

#pragma endregion

};
