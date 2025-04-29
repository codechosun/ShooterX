// DXPlayerController.cpp


#include "Controller/DXPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

void ADXPlayerController::BeginPlay()
{
	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);

	if (IsValid(NotificationTextUIClass) == true)
	{
		UUserWidget* NotificationTextUI = CreateWidget<UUserWidget>(this, NotificationTextUIClass);
		if (IsValid(NotificationTextUI) == true)
		{
			NotificationTextUI->AddToViewport(1);

			NotificationTextUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ADXPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}
