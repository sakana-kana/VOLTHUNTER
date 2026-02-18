//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "ClearCameraParam/ClearCameraPhaseParam.h"
//#include "CameraClearHandler.generated.h"
//
//class USpringArmComponent;
//class APlayerCharacter;
//class APlayerController;
///**
// * 
// */
//UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
//class HIGHSPEEDACTIONGAME_API UCameraClearHandler : public UObject
//{
//	GENERATED_BODY()
//	
//public:
//    // 初期化
//    void Initialize(APlayerCharacter* InPlayer, APlayerController* InController, USpringArmComponent* InSpringArm);
//
//    // 演出開始
//    void StartClearSequence();
//
//    // 強制終了・リセット
//    void ResetSequence();
//
//    // 毎フレーム更新（演出中ならtrueを返す）
//    bool UpdateClearCamera(float DeltaTime);
//
//    // 演出中かどうか
//    bool IsActive() const { return bIsActive; }
//
//protected:
//    // --- パラメータ（エディタで調整できるようにUPROPERTYにする） ---
//    UPROPERTY(EditAnywhere, Category = "ClearCamera")
//    FClearCameraPhaseParam BackParams;
//
//    UPROPERTY(EditAnywhere, Category = "ClearCamera")
//    FClearCameraPhaseParam SideParams;
//
//    UPROPERTY(EditAnywhere, Category = "ClearCamera")
//    FClearCameraPhaseParam FrontParams;
//
//    UPROPERTY(EditAnywhere, Category = "ClearCamera")
//    float ZoomInterpSpeed = 0.3f;
//
//private:
//    // フェーズごとの処理
//    void SetBackPhase();
//    void SetSidePhase();
//    void SetFrontPhase();
//
//    // 内部参照
//    UPROPERTY()
//    APlayerCharacter* Player;
//    UPROPERTY()
//    APlayerController* Controller;
//    UPROPERTY()
//    USpringArmComponent* SpringArm;
//
//    // 状態管理
//    bool bIsActive = false;
//    float CurrentArmLength = 0.f;
//    float TargetArmLength = 0.f;
//
//    FVector CurrentTargetOffset;
//    FVector TargetTargetOffset;
//
//    // タイマーハンドル（ここで管理すればメインクラスは汚れない）
//    FTimerHandle TimerHandle_Back;
//    FTimerHandle TimerHandle_Side;
//    FTimerHandle TimerHandle_Front;
//};
