// Fill out your copyright notice in the Description page of Project Settings.


#include "DashAnimNotifyState.h"
#include "GameFramework/Character.h"
#include "../../GameUtility/GameUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"

void UDashAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	if (!MeshComp)return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());

	if (Character) {
		CachedCharacter = Character;
		m_StartLocation = Character->GetActorLocation();
		m_HasStopped = false;


		m_SpeedBeforeSprint = Character->GetCharacterMovement()->MaxWalkSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeed = DashSpeed;
		//プレイヤーに引っかからないようにするために
		UCapsuleComponent* Capsule = CachedCharacter->GetCapsuleComponent();

		Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);

		CachedCharacter->GetCharacterMovement()->bUseRVOAvoidance = false;
	}

}
void UDashAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DeltaTime) {
	if (!CachedCharacter.IsValid())return;
	if (m_HasStopped)return;

	if (m_EnableWallCheck) {
		if (IsWallInFront()) {
			ResetParam();
			m_HasStopped = true;
			return;
		}
	}

	FVector Forward = CachedCharacter->GetActorForwardVector();
	CachedCharacter->AddMovementInput(Forward, 1.f);
}
void UDashAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	ResetParam();
}


bool UDashAnimNotifyState::IsWallInFront()const {
	if (!CachedCharacter.IsValid())
	{
		return false;
	}

	FVector Start = CachedCharacter->GetActorLocation();
	FVector Forward = CachedCharacter->GetActorForwardVector();
	FVector End = Start + Forward * m_WallJudgmentLength;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CachedCharacter.Get());

	UWorld* World = CachedCharacter->GetWorld();
	if (World)
	{
		bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, QueryParams);

		//DrawDebugLine(World, Start, End, FColor::Green, false, 0.1f, 0, 1.0f);

		if (bHit && HitResult.bBlockingHit)
		{
			AActor* HitActor = HitResult.GetActor();

			if (HitActor)
			{
				// EnemyまたはPlayerタグが付いていたら壁判定を無視（falseを返す）
				if (HitActor->ActorHasTag(FName("Enemy")) || HitActor->ActorHasTag(FName("Player")))
				{
					return false;
				}
			}

			// それ以外はStaticMeshActorであれば壁判定true
			if (HitActor && HitActor->IsA<AStaticMeshActor>())
			{
				return true;
			}
		}
	}

	return false;
}

void UDashAnimNotifyState::ResetParam() {
	if (!CachedCharacter.IsValid())return;
	CachedCharacter->GetCharacterMovement()->bUseRVOAvoidance = true;

	UCapsuleComponent* Capsule = CachedCharacter->GetCapsuleComponent();

	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CachedCharacter->GetCharacterMovement()->MaxWalkSpeed = m_SpeedBeforeSprint;
	m_SpeedBeforeSprint = 0.f;
	CachedCharacter = nullptr;
}