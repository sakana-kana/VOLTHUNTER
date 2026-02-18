// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DashAnimNotifyState.generated.h"

/**
 *
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UDashAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

private:
	bool IsWallInFront()const;
	void ResetParam();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashSpeed = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float m_WallJudgmentLength = 300.f;//•Ç”»’è‚Ì’·‚³

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	bool m_EnableWallCheck = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashDistance = 600.f;
private:
	TWeakObjectPtr<ACharacter> CachedCharacter = nullptr;
	float m_SpeedBeforeSprint = 0.f;

	FVector m_StartLocation = FVector::ZeroVector;

	bool m_HasStopped = false;


};