//’S“–
//ˆÉ“¡’¼÷

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AddElectGauge_Notifiy.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UAddElectGauge_Notifiy : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	//UŒ‚‚Å‘‚¦‚é—Ê
	// ‚±‚ÌUŒ‚‚Å‘‚¦‚éƒQ[ƒW—Ê
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ElectroGauge")
	float m_AddGaugeAmount;
};
