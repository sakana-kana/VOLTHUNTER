//担当
//伊藤直樹

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PlayerAttackSound_NotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UPlayerAttackSound_NotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	// ヒットしたときに鳴らす音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HitSoundToPlay;

	// ヒットしなかったとき鳴らす音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* NoHitSoundToPlay;

	// NotifyState開始
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// NotifyState終了
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// Tick
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

private:
	TSet<AActor*> AlreadyHitActors;
	bool bHasHitSomething = false;
};
