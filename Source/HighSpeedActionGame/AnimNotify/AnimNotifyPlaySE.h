// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyPlaySE.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UAnimNotifyPlaySE : public UAnimNotify
{
	GENERATED_BODY()

public:
    // çƒê∂Ç∑ÇÈÉTÉEÉìÉh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundBase> m_SoundToPlay;

    // Notifyî≠ìÆéûÇ…åƒÇŒÇÍÇÈ
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
