// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackGetEnemyLocation.h"
#include "../../PlayerCharacter.h"
#include "../../PlayerComponent/Player_AttackComponent.h"
#include "../../PlayerComponent/Player_MovementComponent.h"


void UAttackGetEnemyLocation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp) return;

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		if (UPlayer_AttackComponent* AttackComp = PlayerCharacter->FindComponentByClass<UPlayer_AttackComponent>())
		{
			if (UPlayer_MovementComponent* MovementComp = PlayerCharacter->FindComponentByClass<UPlayer_MovementComponent>())
			{

				//ƒWƒƒƒ“ƒv’†‚È‚ç
				if (MovementComp->GetIsJump())
				{
					AttackComp->AirDashAttack();
					return;
				}
				else {
					AttackComp->AttackFirstStepBegin();
				}
			}
		}
	}
}

void UAttackGetEnemyLocation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp) return;

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		if (UPlayer_AttackComponent* AttackComp = PlayerCharacter->FindComponentByClass<UPlayer_AttackComponent>())
		{
			//UŒ‚’†‚ÌŠÔ‡‚¢‹l‚ß
			AttackComp->AttackFirstStepTick();
		}
	}

}

void UAttackGetEnemyLocation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		if (UPlayer_AttackComponent* AttackComp = PlayerCharacter->FindComponentByClass<UPlayer_AttackComponent>())
		{
			//UŒ‚’†‚ÌŠÔ‡‚¢‹l‚ß
			AttackComp->AttackFirstStepEnd();
		}
	}

}
