// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraOpeningHandler.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

namespace OpeningConstants
{
	constexpr float FaceSocketOffsetZ = 70.f;  //顔の高さに合わせるためのZ軸オフセット
	constexpr float StartPitchAngle = -10.f; //演出開始時の見上げる/見下ろす角度
	constexpr float UiFadeDuration = 0.5f;  //UIがフェードアウトするのにかかる秒数
	constexpr float EaseExp = 4.0f;  //カメラ移動のイージングの強さ
}

void UCameraOpeningHandler::Initialize(USpringArmComponent* InSpringArm, UCameraComponent* InCamera, APlayerController* InPC)
{
	m_SpringArm = InSpringArm;
	m_PlayerController = InPC;

	m_IsActive = false;
}

void UCameraOpeningHandler::StartOpening(float WaitTime, float MoveDuration, float FaceDistance, float StartYawOffset)
{
	if (!m_SpringArm.IsValid() || !m_PlayerController.IsValid()) return;

	m_IsActive = true;
	m_CurrentTime = 0.0;
	// 時間を保存
	//待機時間
	m_WaitTime = WaitTime;         
	//移動にかける時間
	m_MoveDuration = MoveDuration; 
	m_StartYawOffset = StartYawOffset;
	m_IsUiHidden = false;

	//UIの生成と表示
	if (OpeningWidgetClass && m_PlayerController.IsValid())
	{
		// 既存があれば念の為消す
		if (m_CreatedWidget)
		{
			m_CreatedWidget->RemoveFromParent();
			m_CreatedWidget = nullptr;
		}

		// 生成 (CreateWidget)
		m_CreatedWidget = CreateWidget<UUserWidget>(m_PlayerController.Get(), OpeningWidgetClass);

		// 画面に追加 (AddToViewport)
		if (m_CreatedWidget)
		{
			m_CreatedWidget->AddToViewport();
		}
	}

	//目標値（通常プレイ状態）を保存
	m_InitialArmLength = m_SpringArm->TargetArmLength;
	m_InitialSocketOffset = m_SpringArm->SocketOffset;
	m_InitialRotation = m_PlayerController->GetControlRotation();

	//開始位置
	m_StartArmLength = FaceDistance;

	//顔の高さへ
	m_FaceSocketOffset = m_InitialSocketOffset;
	m_FaceSocketOffset.Z = OpeningConstants::FaceSocketOffsetZ;

	//カメラを開始位置へ
	FRotator StartRotation = m_InitialRotation;
	StartRotation.Yaw += m_StartYawOffset;
	StartRotation.Pitch = OpeningConstants::StartPitchAngle;

	m_PlayerController->SetControlRotation(StartRotation);
	m_SpringArm->TargetArmLength = m_StartArmLength;
	m_SpringArm->SocketOffset = m_FaceSocketOffset;
}

bool UCameraOpeningHandler::UpdateOpening(float DeltaTime)
{
	if (!m_IsActive || !m_SpringArm.IsValid() || !m_PlayerController.IsValid()) return false;

	m_CurrentTime += DeltaTime;

	//待機時間はカメラ動かさない
	if (m_CurrentTime < m_WaitTime)
	{
		return true;
	}

	//経過時間から待機時間を引いて、移動に使った時間出す
	float MoveTime = m_CurrentTime - m_WaitTime;

	if (!m_IsUiHidden && m_CreatedWidget)
	{
		float FadeStartTime = UiHideDelayTime;
		float FadeEndTime = UiHideDelayTime + OpeningConstants::UiFadeDuration;

		//「消える時間」のどれくらい手前か
		//RemainingTime が 0.5 以下になったらフェード開始
		float RemainingTime = UiHideDelayTime - MoveTime;

		if (MoveTime >= FadeEndTime)
		{
			//時間切れ：完全に削除
			m_CreatedWidget->RemoveFromParent();
			m_CreatedWidget = nullptr;
			m_IsUiHidden = true;
		}
		else if (MoveTime >= FadeStartTime)
		{
			//フェード中：時間経過に合わせて Opacity を 1.0 -> 0.0 に補間
			float Opacity = FMath::GetMappedRangeValueClamped(
				FVector2D(FadeStartTime, FadeEndTime),
				FVector2D(1.0f, 0.0f),
				MoveTime
			);
			m_CreatedWidget->SetRenderOpacity(Opacity);
		}
		else
		{
			//フェード開始前：完全に不透明
			m_CreatedWidget->SetRenderOpacity(1.0f);
		}
	}
	//進行割合 (0.0 ~ 1.0)
	float Alpha = FMath::Clamp(MoveTime / m_MoveDuration, 0.f, 1.f);

	//イージング関数でなめらかに（EaseInOut）
	float SmoothAlpha = FMath::InterpEaseInOut(0.0f, 1.0f, Alpha, OpeningConstants::EaseExp);

	//補間の適用
	m_SpringArm->TargetArmLength = FMath::Lerp(m_StartArmLength, m_InitialArmLength, SmoothAlpha);
	m_SpringArm->SocketOffset = FMath::Lerp(m_FaceSocketOffset, m_InitialSocketOffset, SmoothAlpha);

	FRotator StartRotation = m_InitialRotation;
	StartRotation.Yaw += m_StartYawOffset;
	StartRotation.Pitch = OpeningConstants::StartPitchAngle;

	FRotator NewRotation = FMath::Lerp(StartRotation, m_InitialRotation, SmoothAlpha);
	m_PlayerController->SetControlRotation(NewRotation);

	//終了判定
	if (Alpha >= 1.0f)
	{
		StopOpening();
		return false; //演出終了を通知
	}

	return true; //演出継続
}

void UCameraOpeningHandler::StopOpening()
{
	m_IsActive = false;

	//UIが残っていれば削除
	if (m_CreatedWidget)
	{
		m_CreatedWidget->RemoveFromParent();
		m_CreatedWidget = nullptr;
	}

	//カメラを最終目標値（通常状態）に確実にセット
	if (m_SpringArm.IsValid())
	{
		m_SpringArm->TargetArmLength = m_InitialArmLength;
		m_SpringArm->SocketOffset = m_InitialSocketOffset;
	}

	if (m_PlayerController.IsValid())
	{
		m_PlayerController->SetControlRotation(m_InitialRotation);
	}
}
