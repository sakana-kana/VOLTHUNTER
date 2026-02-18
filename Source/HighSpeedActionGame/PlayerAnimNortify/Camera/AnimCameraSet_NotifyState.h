//担当
//伊藤直樹

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimCameraSet_NotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UAnimCameraSet_NotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:

	// --- オーバーライド関数 ---
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


	//設定項目
	//カメラの距離を変えるか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Override", meta = (InlineEditConditionToggle))
	bool bEnableArmLength = true;

	//カメラの距離
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Override", meta = (EditCondition = "bEnableArmLength"))
	float TargetArmLength = 300.0f;

	// 視野角を変更するか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Override", meta = (InlineEditConditionToggle))
	bool bEnableFOV = true;

	//視野角
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Override", meta = (EditCondition = "bEnableFOV"))
	float TargetFOV = 90.0f;

	// 変化のスピード（補間速度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Override")
	float InterpSpeed = 10.0f;

};

