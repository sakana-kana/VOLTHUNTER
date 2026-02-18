// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "../Widget/TitleModeSelectWidge.h"
#include "Kismet/KismetSystemLibrary.h"

namespace {
	constexpr int8 MaxMenuWindowNum = 3;
}

void ATitlePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if (Subsystem)
		{
			Subsystem->AddMappingContext(TitleMappingContext, 0);
		}
	}

	// ウィジェット生成＆表示
	if (ModeSelectWidgetClass)
	{
		ModeSelectWidget = CreateWidget<UTitleModeSelectWidge>(this, ModeSelectWidgetClass);
		if (ModeSelectWidget)
		{
			ModeSelectWidget->AddToViewport();
			IsModeSelectOpen = false;
		}
	}
}
void ATitlePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIComp = CastChecked<UEnhancedInputComponent>(InputComponent);

	EIComp->BindAction(m_DecisionAction, ETriggerEvent::Triggered, this, &ATitlePlayerController::DecisionAction);
	EIComp->BindAction(m_ReturnAction, ETriggerEvent::Triggered, this, &ATitlePlayerController::ReturnAction);
	EIComp->BindAction(m_MoveUpSelectionAction, ETriggerEvent::Started, this, &ATitlePlayerController::MoveUpSelection);
	EIComp->BindAction(m_MoveDownSelectionAction, ETriggerEvent::Started, this, &ATitlePlayerController::MoveDownSelection);

}

void ATitlePlayerController::DecisionAction(const FInputActionValue& Value)
{
	if (ModeSelectWidget) {
		if (!ModeSelectWidget->GetIsAnimationPlaying() && !IsModeSelectOpen) {
			ETitleMenuInputType Type = ETitleMenuInputType::Decision;
			ModeSelectWidget->NotifyInput(Type, m_CurrentIndex);
			IsModeSelectOpen = true;
			return;
		}
		else if (MaxMenuWindowNum == m_CurrentIndex) {
			APlayerController* PC = this;
			if (PC) {
				UKismetSystemLibrary::QuitGame(PC, PC, EQuitPreference::Quit, false);
			}
		}
		else if (!ModeSelectWidget->GetIsAnimationPlaying() && IsModeSelectOpen) {
			if (!LevelAssetToLoad[m_CurrentIndex].IsNull()) {
				UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelAssetToLoad[m_CurrentIndex]);
			}
		}
	}
}

void ATitlePlayerController::ReturnAction(const FInputActionValue& Value) {
	if (ModeSelectWidget) {
		if (!ModeSelectWidget->GetIsAnimationPlaying() && IsModeSelectOpen) {
			ETitleMenuInputType Type = ETitleMenuInputType::Cancel;
			ModeSelectWidget->NotifyInput(Type, m_CurrentIndex);
			IsModeSelectOpen = false;
		}

	}
}

void ATitlePlayerController::MoveUpSelection(const FInputActionValue& Value) {
	if (!IsModeSelectOpen && ModeSelectWidget->GetIsAnimationPlaying())return;

	--m_CurrentIndex;

	if (m_CurrentIndex < 0) {
		m_CurrentIndex = MaxMenuWindowNum;
	}
	ETitleMenuInputType Type = ETitleMenuInputType::MoveUpSelection;
	ModeSelectWidget->NotifyInput(Type, m_CurrentIndex);

}
void ATitlePlayerController::MoveDownSelection(const FInputActionValue& Value) {
	if (!IsModeSelectOpen && ModeSelectWidget->GetIsAnimationPlaying())return;

	++m_CurrentIndex;
	if (m_CurrentIndex > MaxMenuWindowNum) {
		m_CurrentIndex = 0;
	}
	ETitleMenuInputType Type = ETitleMenuInputType::MoveDownSelection;
	ModeSelectWidget->NotifyInput(Type, m_CurrentIndex);

}