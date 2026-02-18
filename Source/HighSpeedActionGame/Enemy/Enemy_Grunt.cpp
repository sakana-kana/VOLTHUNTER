// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Grunt.h"
#include "../PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet//KismetMathLibrary.h"

#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "Math/UnrealMathUtility.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Animation/AnimMontage.h"
#include "EnemyAIController/GruntAIController.h"


AEnemy_Grunt::AEnemy_Grunt()
	:m_Timer(0.f)
{
	// AddUniqueでタグが重複しないようになる//Editorから生成した敵もプールに入れるためここでタグセット
	Tags.AddUnique(FName(TEXT("Enemy_1")));
}

void AEnemy_Grunt::BeginPlay() {
	Super::BeginPlay();
}

void AEnemy_Grunt::Tick(float DeltaTime) {
	if (!m_IsActive)return;
	Super::Tick(DeltaTime);
}


void AEnemy_Grunt::TakeDamage(const FDamageInfo& _damageInfo) {
	if (!m_IsTakeDamage || m_IsDeath)return;

	AEnemyBase::TakeDamage(_damageInfo);
}

void AEnemy_Grunt::SetAIControllerIsActive(const bool _isActive) {
	Super::SetAIControllerIsActive(_isActive);

	AGruntAIController* AI = Cast<AGruntAIController>(GetController());
	if (AI)
	{
		AI->SetAIActive(_isActive);
	}
}