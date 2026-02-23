// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PlayMontage.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/AnimMontage.h"
#include "AIController.h"

UBTT_PlayMontage::UBTT_PlayMontage()
{
	NodeName = TEXT("Play Montage And Wait");
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTT_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
	ACharacter* Character = Pawn ? Cast<ACharacter>(Pawn) : nullptr;

	if (!Character || !MontageToPlay)
		return EBTNodeResult::Failed;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance)return EBTNodeResult::Failed;

	AnimInstance->Montage_Play(MontageToPlay);

	return EBTNodeResult::InProgress;
}

void UBTT_PlayMontage::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	APawn* Pawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
	ACharacter* Character = Pawn ? Cast<ACharacter>(Pawn) : nullptr;

	if (!Character)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// Ä¶‚µ‚Ä‚¢‚È‚¯‚ê‚ÎI—¹
	if (!AnimInstance->Montage_IsPlaying(MontageToPlay))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

void UBTT_PlayMontage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (!OwnerComp)
		return;

	if (bInterrupted)
	{
		// “r’†’âŽ~‚È‚çŽ¸”sˆµ‚¢i‚±‚±‚ªd—vj
		FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		// ³íI—¹
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}

	// Delegate‰ðœ
	APawn* Pawn = OwnerComp->GetAIOwner() ? OwnerComp->GetAIOwner()->GetPawn() : nullptr;
	ACharacter* Character = Pawn ? Cast<ACharacter>(Pawn) : nullptr;
	if (Character)
	{
		UAnimInstance* AnimInstance = Character->GetMesh() ? Character->GetMesh()->GetAnimInstance() : nullptr;
		if (AnimInstance)
		{
			AnimInstance->OnMontageEnded.RemoveAll(this);
		}
	}

	m_DelegateBound = false;
}

