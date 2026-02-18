//#include "CameraClearHandler.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "GameFramework/PlayerController.h"
//#include "../../../PlayerCharacter.h" // パスは合わせてください
//#include "GameFramework/CharacterMovementComponent.h"
//#include "TimerManager.h"
//
//void UCameraClearHandler::Initialize(APlayerCharacter* InPlayer, APlayerController* InController, USpringArmComponent* InSpringArm)
//{
//    Player = InPlayer;
//    Controller = InController;
//    SpringArm = InSpringArm;
//
//    // パラメータのデフォルト値を設定（必要ならBPで上書き可能）
//    // 例: SideParams.AddYaw = 90.f; など
//}
//
//void UCameraClearHandler::StartClearSequence()
//{
//    if (!Player || !Controller || !SpringArm) return;
//
//    bIsActive = true;
//
//    // キャラクターの回転制御を停止
//    if (UCharacterMovementComponent* MoveComp = Player->GetCharacterMovement())
//    {
//        MoveComp->bOrientRotationToMovement = false;
//    }
//    SpringArm->bUsePawnControlRotation = true;
//
//    SpringArm->bDoCollisionTest = false;
//    // 現在の長さを取得
//    CurrentArmLength = SpringArm->TargetArmLength;
//    CurrentTargetOffset = SpringArm->TargetOffset;
//
//
//
//    UWorld* World = Player->GetWorld();
//    if (!World) return;
//
//    // --- タイマーセット ---
//
//    // 即時：背面
//    World->GetTimerManager().SetTimer(TimerHandle_Back, this, &UCameraClearHandler::SetBackPhase, 0.1f, false); // 即時実行に近い
//
//    // 3秒後：横
//    World->GetTimerManager().SetTimer(TimerHandle_Side, this, &UCameraClearHandler::SetSidePhase, 3.0f, false);
//
//    // 4.33秒後：正面
//    World->GetTimerManager().SetTimer(TimerHandle_Front, this, &UCameraClearHandler::SetFrontPhase, 4.33f, false);
//}
//
//void UCameraClearHandler::ResetSequence()
//{
//    bIsActive = false;
//
//    if (SpringArm)
//    {
//        SpringArm->bDoCollisionTest = true;
//        // TargetOffsetなども戻したい場合はここで初期値をセット
//    }
//
//    if (Player)
//    {
//        UWorld* World = Player->GetWorld();
//        if (World)
//        {
//            World->GetTimerManager().ClearTimer(TimerHandle_Back);
//            World->GetTimerManager().ClearTimer(TimerHandle_Side);
//            World->GetTimerManager().ClearTimer(TimerHandle_Front);
//        }
//    }
//
//    // ここでControlRotationを戻す処理などが必要なら記述
//    // （メインコンポーネント側のResetCameraで一括リセットする設計ならここはタイマー停止だけでOK）
//}
//
//bool UCameraClearHandler::UpdateClearCamera(float DeltaTime)
//{
//    if (!bIsActive || !SpringArm) return false;
//
//    // ズーム補間
//    CurrentArmLength = FMath::FInterpTo(CurrentArmLength, TargetArmLength, DeltaTime, ZoomInterpSpeed);
//    SpringArm->TargetArmLength = CurrentArmLength;
//
//    return true; // 「今クリア演出中だよ」と伝える
//}
//
//void UCameraClearHandler::SetBackPhase()
//{
//    // パラメータ適用
//    FRotator Rot = Player->GetActorRotation();
//    Rot.Yaw += BackParams.AddYaw;
//    Rot.Pitch = BackParams.Pitch;
//    Controller->SetControlRotation(Rot);
//
//    TargetArmLength = BackParams.TargetArmLength;
//    SpringArm->TargetOffset = BackParams.TargetOffset;
//    SpringArm->SocketOffset = BackParams.SocketOffset;
//}
//
//void UCameraClearHandler::SetSidePhase()
//{
//    FRotator Rot = Player->GetActorRotation();
//    Rot.Yaw += SideParams.AddYaw;
//    Rot.Pitch = SideParams.Pitch;
//    Controller->SetControlRotation(Rot);
//
//    TargetArmLength = SideParams.TargetArmLength;
//    SpringArm->TargetOffset = SideParams.TargetOffset;
//    SpringArm->SocketOffset = SideParams.SocketOffset;
//}
//
//void UCameraClearHandler::SetFrontPhase()
//{
//    FRotator Rot = Player->GetActorRotation();
//    Rot.Yaw += FrontParams.AddYaw;
//    Rot.Pitch = FrontParams.Pitch;
//    Controller->SetControlRotation(Rot);
//
//    TargetArmLength = FrontParams.TargetArmLength;
//    SpringArm->TargetOffset = SideParams.TargetOffset;
//    SpringArm->SocketOffset = FrontParams.SocketOffset;
//}