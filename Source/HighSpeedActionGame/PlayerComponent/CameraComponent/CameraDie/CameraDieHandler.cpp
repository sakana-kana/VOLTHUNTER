// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDieHandler.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

void UCameraDieHandler::Initialize(USpringArmComponent* InSpringArm, APlayerController* InController)
{
	m_SpringArm = InSpringArm;
	m_PlayerController = InController;
	m_IsActive = false;
}

void UCameraDieHandler::StartDieCamera()
{
	if (!m_SpringArm.IsValid() || !m_PlayerController.IsValid()) return;

	m_IsActive = true;

	//プレイヤーによるカメラ操作無効
	m_SpringArm->bUsePawnControlRotation = false;

	//死んだ瞬間のワールド座標を保存
	FVector CurrentWorldLoc = m_SpringArm->GetComponentLocation();

	//親（プレイヤー）の動きを完全に無視して、その場に留まる
	m_SpringArm->SetUsingAbsoluteLocation(true);

	//親（プレイヤーの体）が倒れる回転の影響を完全に無視する（絶対回転化）
	m_SpringArm->SetUsingAbsoluteRotation(true);

	//保存しておいた死んだ瞬間の位置に引き戻して固定
	m_SpringArm->SetWorldLocation(CurrentWorldLoc);

	//カメラが床にぶつかってガクガク押し出されるのを防ぐ
	m_SpringArm->bDoCollisionTest = false;

	m_SpringArm->bEnableCameraLag = false;
	m_SpringArm->bEnableCameraRotationLag = false;

	//距離を瞬時に変更
	m_SpringArm->TargetArmLength += m_DieZoomOutDistance;

	//コントローラーの回転を取得
	FRotator DieRot = m_PlayerController->GetControlRotation();
	DieRot.Pitch = m_TargetPitch;
	//画面が斜めに傾かないように強制リセット
	DieRot.Roll = 0.0f; 

	//World（絶対）で回転をセットする
	m_SpringArm->SetWorldRotation(DieRot);
}

void UCameraDieHandler::EndDieCamera()
{
	// アクティブじゃなければ何もしない
	if (!m_IsActive) return;

	m_IsActive = false;

	if (m_SpringArm.IsValid())
	{
		m_SpringArm->SetUsingAbsoluteLocation(false);
		m_SpringArm->SetUsingAbsoluteRotation(false);
		m_SpringArm->bDoCollisionTest = true;

	}
}

