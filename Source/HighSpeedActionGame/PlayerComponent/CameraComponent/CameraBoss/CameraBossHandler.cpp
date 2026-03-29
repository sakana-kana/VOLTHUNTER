// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBossHandler.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void UCameraBossHandler::Initialize(USpringArmComponent* InSpringArm, UCameraComponent* InCamera)
{
	m_SpringArm = InSpringArm;
	m_Camera = InCamera;
	m_IsActive = false;
}

void UCameraBossHandler::StartBossCamera()
{
	if (!m_SpringArm.IsValid() || !m_Camera.IsValid()) return;

	m_IsActive = true;

	//現在の値を保持
	m_DefaultArmLength = m_SpringArm->TargetArmLength;
	m_DefaultFOV = m_Camera->FieldOfView;
}

void UCameraBossHandler::EndBossCamera()
{
	m_IsActive = false;
}

bool UCameraBossHandler::UpdateBossCamera(float DeltaTime)
{
	if (!m_IsActive || !m_SpringArm.IsValid() || !m_Camera.IsValid()) return false;


	//ボス用のカメラ距離へ補間
	m_SpringArm->TargetArmLength = FMath::FInterpTo(
		m_SpringArm->TargetArmLength,
		m_BossArmLength,
		DeltaTime,
		m_TransitionSpeed
	);

	//ボス用のFOVへ補間
	m_Camera->SetFieldOfView(FMath::FInterpTo(
		m_Camera->FieldOfView,
		m_BossFOV,
		DeltaTime,
		m_TransitionSpeed
	));

	return true;
}

bool UCameraBossHandler::IsActive()const {
	return m_IsActive;
}
