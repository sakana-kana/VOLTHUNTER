//担当
//伊藤直樹

//剣のトレイルクラス

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
	// Notify 詳細から選択する対象の刀クラス
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sword")
	TSubclassOf<APlayerSword> TargetSwordClass;
};
