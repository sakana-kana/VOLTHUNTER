// 
#include "HitJudgmentComponent.h"
#include "../AttackCollisionDetection/AttackCollisionDetection.h"
#include "../AttackCollisionDetection/AttackCollisionHandle/AttackCollisionHandle.h"
#include "../AttackCollisionDetection/AttackCollisionPoolSubsystem/AttackCollisionPoolSubsystem.h"

namespace {
	constexpr int8 PoolSize = 10;
}


// Sets default values for this component's properties
UHitJudgmentComponent::UHitJudgmentComponent()
{
	//Tickオフ
	PrimaryComponentTick.bCanEverTick = false;
}

UHitJudgmentComponent::~UHitJudgmentComponent() {

}

// Called when the game starts
void UHitJudgmentComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UHitJudgmentComponent::BeginHitDetection(FDamageInfo& _damageinfo, const float _radius, FVector& _relativeLocation, const AActor& _actor, const TArray<FString>& _tag) {


	m_CollisionDetectionUser = &_actor;

	// World からプール Subsystem を取得
	UAttackCollisionPoolSubsystem* Pool = GetWorld()->GetSubsystem<UAttackCollisionPoolSubsystem>();

	if (!Pool) return;

	CollisionHandle = Pool->AcquireHandle();

	if (!CollisionHandle.IsValid()) return;

	FVector CharacterLocation = m_CollisionDetectionUser->GetActorLocation();
	FRotator CharacterRotation = m_CollisionDetectionUser->GetActorRotation();
	FVector WorldOffset = CharacterRotation.RotateVector(_relativeLocation);
	FVector RelativeLocation = CharacterLocation + WorldOffset;

	CollisionHandle.Initialize(*this, _damageinfo, RelativeLocation, _tag, _radius);

}

void UHitJudgmentComponent::PossibleHitTime(FVector& _relativeLocation) {
	SetLocationRelativeToActorRotation(_relativeLocation);
}

void UHitJudgmentComponent::EndHitDetection() {
	CollisionHandle.Release();
}

void UHitJudgmentComponent::SetAttackCollisionDetectionVisible(const bool _isVisible) {
	if (!CollisionHandle.IsValid()) return;
	CollisionHandle.SetVisible(_isVisible);
}

void UHitJudgmentComponent::SetRadius(const float _radius) {

}

void UHitJudgmentComponent::SetLocationRelativeToActorRotation(const FVector _relativeLocation) {
	if (!m_CollisionDetectionUser || !CollisionHandle.IsValid())return;

	FVector CharacterLocation = m_CollisionDetectionUser->GetActorLocation();
	FRotator CharacterRotation = m_CollisionDetectionUser->GetActorRotation();
	FVector WorldOffset = CharacterRotation.RotateVector(_relativeLocation);

	CollisionHandle.SetCollisionWorldLocation(CharacterLocation + WorldOffset);
}

void UHitJudgmentComponent::NotifyAttackHit(const AActor* _hitActor) const {
	OnAttackHit.Broadcast(_hitActor);
}