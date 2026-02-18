//’S“–
//ˆÉ“¡’¼÷

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Player_SwordEffect.generated.h"

class APlayerSword;

UCLASS()
class HIGHSPEEDACTIONGAME_API UPlayer_SwordEffect : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
protected:
	// Notify Ú×‚©‚ç‘I‘ğ‚·‚é‘ÎÛ‚Ì“ƒNƒ‰ƒX
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sword")
	TSubclassOf<APlayerSword> TargetSwordClass;
};
