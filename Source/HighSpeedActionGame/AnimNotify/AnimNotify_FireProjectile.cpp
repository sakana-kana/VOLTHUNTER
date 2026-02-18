// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_FireProjectile.h"
#include "Engine/World.h"
#include "../Projectile/ProjectileBase.h"
#include "../DataAssets/AttackData.h"

void UAnimNotify_FireProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName);
	FRotator SpawnRotation = MeshComp->GetOwner()->GetActorRotation();

	if (!m_AttackData) {
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, TEXT("No attack dataset!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		return;
	}

	UWorld* World = MeshComp->GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParams.Owner = MeshComp->GetOwner();

		AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(m_Projectile, SpawnLocation, SpawnRotation, SpawnParams);

		if (!Projectile)return;

		Projectile->SetAttackCollisionParam(m_AttackCollisionParam);

		FDamageInfo DamageInfo;
		DamageInfo.AttackActor = MeshComp->GetOwner();
		DamageInfo.Damage = m_AttackData->Damage;
		DamageInfo.KnockbackScale = m_AttackData->KnockbackScale;
		DamageInfo.HitStopTime = m_AttackData->HitStopTime;
		FVector KnockbackVector = SpawnRotation.RotateVector(m_AttackData->KnockbackDirection);
		DamageInfo.KnockbackDirection = KnockbackVector;
		Projectile->SetDamageInfo(DamageInfo);

		//衝突判定スタート
		Projectile->OnCollisionBegin();
	}
}

