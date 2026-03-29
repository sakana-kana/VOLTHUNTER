//担当
//伊藤直樹

//カメラをシェイクさせるクラス

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "SetCameraShakeNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API USetCameraShakeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	// NotifyState開始
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// Tick
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	// NotifyState終了
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

    UPROPERTY(EditAnywhere, Category = "CameraShake")
    TSubclassOf<UCameraShakeBase> CameraShakeClass;

    UPROPERTY(EditAnywhere, Category = "CameraShake")
    float ShakeScale = 1.0f;

	UPROPERTY()
	UNiagaraComponent* SpawnedEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* Effect;

	UPROPERTY(EditAnywhere, Category = "Effect")
	FName EffectSocketName = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Effect")
	FVector EffectOffset = FVector::ZeroVector;

private:
	bool bTriggered;

};
