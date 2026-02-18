// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_TrojanHorseBoss.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../HitStopComponent/HitStopComponent.h"


AEnemy_TrojanHorseBoss::AEnemy_TrojanHorseBoss()
{
	// デフォルトのCapsuleコリジョン無効化
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Capsuleの衝突チャンネルをWorldDynamicに変更
	GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);

	// すべてのチャンネルをIgnoreにしてから
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	// 地面などとのBlockは維持
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	// Pawnとの衝突やOverlapは無効化
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	m_WarpOffsetDistance = 150.f;

	Tags.AddUnique(FName(TEXT("TrojanHorse")));
}

void AEnemy_TrojanHorseBoss::Tick(float DeltaTime) {
	if (!m_IsActive)return;
	Super::Tick(DeltaTime);
}

void AEnemy_TrojanHorseBoss::TakeDamage(const FDamageInfo& _damageInfo) {
	if (!m_HitStopComponent || !m_IsTakeDamage)return;

	m_HitStopComponent->StartHitStop(_damageInfo.HitStopTime);

	m_EnemyParam.m_Hp -= CalculateEnemyDamage(_damageInfo);

	if (m_EnemyParam.m_Hp <= 0)
	{
		OnDying();//瀕死処理呼び出す
	}
}