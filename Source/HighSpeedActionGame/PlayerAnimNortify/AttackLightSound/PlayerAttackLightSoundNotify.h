//’S“–
//ˆÉ“¡’¼Ž÷

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerAttackLightSoundNotify.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UPlayerAttackLightSoundNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	//ƒqƒbƒg‚µ‚½‚Æ‚«‚É–Â‚ç‚·‰¹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HitSoundToPlay;

	//ƒqƒbƒg‚µ‚È‚©‚Á‚½‚Æ‚«–Â‚ç‚·‰¹
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* NoHitSoundToPlay;

	
};
