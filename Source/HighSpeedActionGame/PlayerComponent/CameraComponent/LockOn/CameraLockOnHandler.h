////担当
////伊藤直樹
//
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "CameraLockOnHandler.generated.h"
//
//class UPlayer_CameraComponent;
//class USpringArmComponent;
//class UCameraComponent;
//class APlayerCharacter;
//class APlayerController;
//class AActor;
//
///**
// * ロックオン機能のロジックを担当するハンドラ
// */
//UCLASS()
//class HIGHSPEEDACTIONGAME_API UCameraLockOnHandler : public UObject
//{
//	GENERATED_BODY()
//
//public:
//	// 初期化（依存するコンポーネントやプレイヤーを受け取る）
//	void Initialize(UPlayer_CameraComponent* InOwnerComp, APlayerCharacter* InPlayer, APlayerController* InController,
//		USpringArmComponent* InMainArm, UCameraComponent* InMainCam,
//		USpringArmComponent* InLockOnArm, UCameraComponent* InLockOnCam);
//
//	// 毎フレームの更新処理
//	void UpdateLockOn(float DeltaTime);
//
//	// ロックオンの開始・解除のトグル
//	void ToggleLockOn();
//
//	// ターゲットの切り替え
//	void ChangeTarget();
//
//	// 強制解除
//	void CancelLockOn();
//
//	// 現在のターゲット取得
//	AActor* GetCurrentTarget() const { return m_LockOnTarget; }
//
//private:
//	// 最も近い敵を探す
//	AActor* FindNearestEnemy(FName TagName);
//
//
//private:
//	// 親コンポーネント（フラグ書き換え用）
//	UPROPERTY()
//	UPlayer_CameraComponent* m_OwnerComp;
//
//	// 制御対象のキャッシュ
//	UPROPERTY()
//	APlayerCharacter* m_Player;
//
//	UPROPERTY()
//	APlayerController* m_PlayerController;
//
//	UPROPERTY()
//	USpringArmComponent* m_MainSpringArm;
//
//	UPROPERTY()
//	UCameraComponent* m_MainCamera;
//
//	UPROPERTY()
//	USpringArmComponent* m_LockOnSpringArm;
//
//	UPROPERTY()
//	UCameraComponent* m_LockOnCamera;
//
//	// ロックオンターゲット（Handlerが管理）
//	UPROPERTY()
//	AActor* m_LockOnTarget;
//
//	// 定数パラメータ
//	float m_MaxLockOnDistance = 2500.f;
//};