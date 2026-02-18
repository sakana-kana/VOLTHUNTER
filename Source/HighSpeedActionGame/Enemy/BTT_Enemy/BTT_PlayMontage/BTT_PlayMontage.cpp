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
	bNotifyTick = false; // Tick不要
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTT_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner() ? OwnerComp.GetAIOwner()->GetPawn() : nullptr;
	ACharacter* Character = Pawn ? Cast<ACharacter>(Pawn) : nullptr;
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not a Character"));
		return EBTNodeResult::Failed;
	}

	if (!MontageToPlay)
	{
		UE_LOG(LogTemp, Warning, TEXT("MontageToPlay is null"));
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInstance = Character->GetMesh() ? Character->GetMesh()->GetAnimInstance() : nullptr;
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance is null"));
		return EBTNodeResult::Failed;
	}

	FOnMontageEnded MontageEndedDelegate;
	MontageEndedDelegate.BindUObject(this, &UBTT_PlayMontage::OnMontageEnded, &OwnerComp);

	AnimInstance->Montage_Play(MontageToPlay);

	AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

	return EBTNodeResult::InProgress; // 完了までタスク継続
}

void UBTT_PlayMontage::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, UBehaviorTreeComponent* OwnerComp)
{
	if (OwnerComp)
	{
		FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
	}
}