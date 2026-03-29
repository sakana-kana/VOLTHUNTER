//担当
//伊藤直樹

//霹靂一閃風スキルのエフェクト管理クラス

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "ThunderTrailEffect.generated.h"

class UNiagaraComponent;

UCLASS()
class HIGHSPEEDACTIONGAME_API AThunderTrailEffect : public AActor
{
	GENERATED_BODY()

public:
	AThunderTrailEffect();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//エフェクトのフェードアウト
	UFUNCTION(BlueprintCallable, Category = "Effect")
	void BeginFadeOut();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effect")
	UNiagaraComponent* NiagaraComp;

	//エフェクト調整用パラメータ
	//スケールXを計算する際の基準となる長さ
	UPROPERTY(EditDefaultsOnly, Category = "Effect Setup")
	float BaseEffectLength = 10.0f;
	//エフェクトの太さ
	UPROPERTY(EditDefaultsOnly, Category = "Effect Setup")
	float ThicknessScale = 0.1f;

	//スキル終了時、エフェクトが細くなって消えていく速度
	UPROPERTY(EditDefaultsOnly, Category = "Effect|Fade")
	float FadeOutInterpSpeed = 10.f;

	//フェードアウト開始からActorが完全に削除されるまでの時間（秒）
	UPROPERTY(EditDefaultsOnly, Category = "Effect|Fade")
	float FadeOutLifeSpan = 0.5f;


private:
	//フェードアウト処理中か
	bool bIsFinished = false;
	// 始点座標
	FVector StartLocation;

	// 最初の向き
	FRotator FixedRotation;
};
