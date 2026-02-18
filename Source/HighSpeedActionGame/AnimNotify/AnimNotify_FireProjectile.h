// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../AttackCollisionDetection/AttackCollisionParam.h"
#include "AnimNotify_FireProjectile.generated.h"

class AProjectileBase;
class UAttackData;
/**
 *
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UAnimNotify_FireProjectile : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AProjectileBase> m_Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName SocketName = NAME_None;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackData")
	TObjectPtr<UAttackData> m_AttackData;//çUåÇÇÃÉfÅ[É^

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackData")
	FAttackCollisionParam m_AttackCollisionParam;
};
