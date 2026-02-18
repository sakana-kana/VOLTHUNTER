//#include "CameraLockOnHandler.h"
//#include "../../Player_CameraComponent.h"
//#include "../../../PlayerCharacter.h"
//#include "../../../Enemy/EnemyBase.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetMathLibrary.h"
//
//void UCameraLockOnHandler::Initialize(UPlayer_CameraComponent* InOwnerComp, APlayerCharacter* InPlayer, APlayerController* InController,
//	USpringArmComponent* InMainArm, UCameraComponent* InMainCam,
//	USpringArmComponent* InLockOnArm, UCameraComponent* InLockOnCam)
//{
//	m_OwnerComp = InOwnerComp;
//	m_Player = InPlayer;
//	m_PlayerController = InController;
//	m_MainSpringArm = InMainArm;
//	m_MainCamera = InMainCam;
//	m_LockOnSpringArm = InLockOnArm;
//	m_LockOnCamera = InLockOnCam;
//
//	m_LockOnTarget = nullptr;
//}
//
//void UCameraLockOnHandler::ToggleLockOn()
//{
//	if (!m_OwnerComp) return;
//
//	// 親コンポーネントのフラグを確認
//	if (m_OwnerComp->GetIsTargetLockedOn())
//	{
//		CancelLockOn();
//	}
//	else
//	{
//		AActor* NewTarget = FindNearestEnemy(FName(TEXT("Enemy")));
//		if (NewTarget)
//		{
//			// ターゲットセット
//			m_LockOnTarget = NewTarget;
//
//			// 親コンポーネントのフラグをON
//			m_OwnerComp->SetIsTargetLockedOn(true);
//
//			// キャラクター挙動変更（移動方向への回転をOFF）
//			if (m_Player)
//			{
//				m_Player->GetCharacterMovement()->bOrientRotationToMovement = false;
//			}
//
//			// カメラ切り替え
//			if (m_LockOnCamera && m_MainCamera)
//			{
//				m_LockOnCamera->SetActive(true);
//				m_MainCamera->SetActive(false);
//			}
//		}
//	}
//}
//
//void UCameraLockOnHandler::UpdateLockOn(float DeltaTime)
//{
//	if (!m_OwnerComp || !m_OwnerComp->GetIsTargetLockedOn()) return;
//
//	// ターゲットが無効化されていたら解除
//	AEnemyBase* Enemy = Cast<AEnemyBase>(m_LockOnTarget);
//	if (!Enemy || !Enemy->GetIsActive())
//	{
//		CancelLockOn();
//		return;
//	}
//
//	// 距離チェック
//	FVector PlayerLoc = m_Player->GetActorLocation();
//	FVector TargetLoc = m_LockOnTarget->GetActorLocation();
//	float Distance = FVector::Dist(PlayerLoc, TargetLoc);
//
//	if (Distance > m_MaxLockOnDistance)
//	{
//		CancelLockOn();
//		return;
//	}
//
//	// --- 回転制御 ---
//	FVector Direction = TargetLoc - PlayerLoc;
//	Direction.Z = 0.f;
//
//	if (!Direction.IsNearlyZero())
//	{
//		// ターゲット方向への回転を作成
//		FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
//		FRotator TargetYaw(0.f, LookAtRotation.Yaw, 0.f);
//
//		// プレイヤーの向きを補間
//		if (m_Player)
//		{
//			FRotator CurrentYaw(0.f, m_Player->GetActorRotation().Yaw, 0.f);
//			FRotator NewPlayerRot = FMath::RInterpTo(CurrentYaw, TargetYaw, DeltaTime, 10.f);
//			m_Player->SetActorRotation(NewPlayerRot);
//		}
//
//		// ロックオンカメラアームの向きを補間
//		if (m_LockOnSpringArm)
//		{
//			FRotator CurrentArmRot = m_LockOnSpringArm->GetComponentRotation();
//			FRotator NewArmRot = FMath::RInterpTo(CurrentArmRot, TargetYaw, DeltaTime, 10.f);
//			m_LockOnSpringArm->SetWorldRotation(NewArmRot);
//		}
//	}
//}
//
//void UCameraLockOnHandler::ChangeTarget()
//{
//	if (!m_OwnerComp || !m_OwnerComp->GetIsTargetLockedOn() || !m_LockOnTarget) return;
//
//	// 画面内の敵を検索
//	TArray<AActor*> FoundActors;
//	UGameplayStatics::GetAllActorsWithTag(m_OwnerComp->GetWorld(), FName(TEXT("Enemy")), FoundActors);
//
//	TArray<AEnemyBase*> ActiveEnemies;
//	for (AActor* Actor : FoundActors)
//	{
//		if (!Actor || Actor == m_Player) continue;
//
//		AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
//		if (!Enemy || !Enemy->GetIsActive()) continue;
//
//		// 距離と視界チェック
//		float Distance = FVector::Dist(m_Player->GetActorLocation(), Enemy->GetActorLocation());
//		if (Distance > m_MaxLockOnDistance) continue;
//		if (!m_OwnerComp->IsLocationInCameraView(Enemy->GetActorLocation())) continue;
//
//		ActiveEnemies.Add(Enemy);
//	}
//
//	if (ActiveEnemies.Num() == 0)
//	{
//		CancelLockOn();
//		return;
//	}
//
//	// ターゲット切り替えロジック
//	int32 CurrentIndex = ActiveEnemies.IndexOfByKey(m_LockOnTarget);
//	int32 NextIndex = (CurrentIndex == INDEX_NONE) ? 0 : (CurrentIndex + 1) % ActiveEnemies.Num();
//
//	AEnemyBase* NextEnemy = ActiveEnemies[NextIndex];
//	if (NextEnemy && NextEnemy->GetIsActive())
//	{
//		m_LockOnTarget = NextEnemy;
//		// 既にロックオン状態なのでフラグセットやカメラ切り替えは不要
//	}
//}
//
//void UCameraLockOnHandler::CancelLockOn()
//{
//	m_LockOnTarget = nullptr;
//
//	if (m_OwnerComp)
//	{
//		m_OwnerComp->SetIsTargetLockedOn(false);
//	}
//
//	// プレイヤー挙動リセット
//	if (m_Player)
//	{
//		m_Player->GetCharacterMovement()->bOrientRotationToMovement = true;
//	}
//
//	// コントローラー回転リセット
//	if (m_PlayerController)
//	{
//		FRotator ActorRot = m_Player->GetActorRotation();
//		ActorRot.Pitch = 0.f;
//		ActorRot.Roll = 0.f;
//		m_PlayerController->SetControlRotation(ActorRot);
//	}
//
//	// カメラをメインに戻す
//	if (m_LockOnCamera && m_MainCamera)
//	{
//		m_LockOnCamera->SetActive(false);
//		m_MainCamera->SetActive(true);
//	}
//}
//
//AActor* UCameraLockOnHandler::FindNearestEnemy(FName TagName)
//{
//	if (!m_OwnerComp) return nullptr;
//
//	TArray<AActor*> FoundActors;
//	UGameplayStatics::GetAllActorsWithTag(m_OwnerComp->GetWorld(), TagName, FoundActors);
//
//	float MinDistance = m_MaxLockOnDistance;
//	AActor* NearestTarget = nullptr;
//	FVector PlayerLoc = m_Player->GetActorLocation();
//
//	for (AActor* Actor : FoundActors)
//	{
//		if (!Actor || Actor == m_Player) continue;
//
//		AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
//		if (!Enemy || !Enemy->GetIsActive()) continue;
//
//		if (!m_OwnerComp->IsLocationInCameraView(Enemy->GetActorLocation())) continue;
//
//		float Dist = FVector::Dist(PlayerLoc, Enemy->GetActorLocation());
//		if (Dist < MinDistance)
//		{
//			MinDistance = Dist;
//			NearestTarget = Enemy;
//		}
//	}
//	return NearestTarget;
//}
//
