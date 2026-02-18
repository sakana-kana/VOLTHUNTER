// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../../GameUtility/GameUtility.h"
#include "BehaviorTree/BlackboardComponent.h"

void ABossAIController::BeginPlay() {
	Super::BeginPlay();

	if (m_BehaviorTreeAsset)
	{
		RunBehaviorTree(m_BehaviorTreeAsset);
	}
	// Blackboard‚ÉƒvƒŒƒCƒ„[‚ðTaragetActor‚Æ‚µ‚Ä“o˜^
	auto pBlackBoard = GetBlackboardComponent();
	if (pBlackBoard)
	{
		pBlackBoard->SetValueAsObject(TEXT("TargetActor"), CGameUtility::GetActorFromTag(this->GetWorld(), "Player"));
	}

}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BTAsset)
	{
		RunBehaviorTree(BTAsset);
	}
}
