// Fill out your copyright notice in the Description page of Project Settings.


#include "DashAnimNotifyState.h"
#include "GameFramework/Character.h"
#include "../../GameUtility/GameUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "../../PlayerNotifySubSystem/PlayerNotifySubsystem.h"
#include "Kismet/GameplayStatics.h"

void UDashAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	if (!MeshComp) return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (!Character) return;

	CachedCharacter = Character;

	UCapsuleComponent* Capsule = CachedCharacter->GetCapsuleComponent();

	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);

	m_HasStopped = false;
	m_IsJustEvasion = false;
	m_StopTimer = 0.f;

	// 元の速度保存
	m_OriginalVelocity = Character->GetCharacterMovement()->Velocity;

	// 移動モードをWalking固定
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	UWorld* World = Character->GetWorld();
	if (!World)return;

	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));

	APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());
	if (!PC) return;

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer) return;

	UPlayerNotifySubsystem* CachedNotifySubsystem = LocalPlayer->GetSubsystem<UPlayerNotifySubsystem>();
	if (!CachedNotifySubsystem) return;

	//不都合起きないように一回外して置く（Endが呼ばれない時もあったため）
	CachedNotifySubsystem->OnJustEvasiveOccurred.RemoveDynamic(this, &UDashAnimNotifyState::OnJustEvasiveOccurred);
	CachedNotifySubsystem->OnJustEvasiveOccurred.AddDynamic(this, &UDashAnimNotifyState::OnJustEvasiveOccurred);
}
void UDashAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DeltaTime) {

	if (!CachedCharacter.IsValid()) return;
	if (m_HasStopped) return;

	if (m_IsJustEvasion) {
		m_StopTimer += DeltaTime;
		if (m_StopTimer > m_StopTime) {
			m_HasStopped = true;
		}
	}

	//壁が前にあるなら停止
	if (IsWallInFront())
	{
		CachedCharacter->GetCharacterMovement()->StopMovementImmediately();
		m_HasStopped = true;
		return;
	}

	FVector Forward = CachedCharacter->GetActorForwardVector();
	FVector MoveDelta = Forward * DashSpeed * DeltaTime;

	CachedCharacter->AddActorWorldOffset(MoveDelta, false);
}

void UDashAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (!CachedCharacter.IsValid()) return;

	UCharacterMovementComponent* MoveComp = CachedCharacter->GetCharacterMovement();

	MoveComp->Velocity = m_OriginalVelocity;

	UCapsuleComponent* Capsule = CachedCharacter->GetCapsuleComponent();

	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);

	UWorld* World = GetWorld();

	if (!World)return;

	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));

	APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());
	if (!PC) return;

	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer) return;

	UPlayerNotifySubsystem* CachedNotifySubsystem = LocalPlayer->GetSubsystem<UPlayerNotifySubsystem>();

	if (!CachedNotifySubsystem)return;

	CachedNotifySubsystem->OnJustEvasiveOccurred.RemoveDynamic(this, &UDashAnimNotifyState::OnJustEvasiveOccurred);
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


			if (!HitActor)return false;

			// EnemyまたはPlayerタグが付いていたら壁判定を無視（falseを返す）
			if (HitActor->ActorHasTag(FName("Enemy")) || HitActor->ActorHasTag(FName("Player")))
			{
				return false;
			}

			// 壁のタグがついてるまたはStaticMeshActorであれば壁判定true
			if (HitActor->ActorHasTag(FName("Wall")) || HitActor->IsA<AStaticMeshActor>())
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

void UDashAnimNotifyState::OnJustEvasiveOccurred(const AActor* Attacker) {
	if (!CachedCharacter.IsValid())	return;

	m_IsJustEvasion = true;
}