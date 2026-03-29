//担当
//伊藤直樹

//Spline移動クラス

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player_SplineMove.generated.h"

class APlayerCharacter;
class USplineComponent;
class UBoxComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UPlayer_EvasiveComponent;
class UPlayer_AttackComponent;
class UPlayer_SkillComponent;
class UWidgetComponent;

UCLASS()
class HIGHSPEEDACTIONGAME_API APlayer_SplineMove : public AActor
{
	GENERATED_BODY()

public:
	APlayer_SplineMove();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//プレイヤー側から移動開始を要求
	void RequestStartSplineMove(AActor* RequestActor);

protected:
	//アクセス可能範囲に入った/出た時
	UFUNCTION()
	void OnStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	TWeakObjectPtr<APlayerCharacter> m_Player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component")
	TWeakObjectPtr<UPlayer_EvasiveComponent> m_EvasiveComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component")
	TWeakObjectPtr<UPlayer_AttackComponent> m_AttackComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component")
	TWeakObjectPtr<UPlayer_SkillComponent> m_SkillComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	USplineComponent* m_Spline;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* m_StartCollision;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* m_SplineEffectComponent;

	UPROPERTY(EditAnywhere, Category = "SplineMove|Effect")
	UNiagaraSystem* m_SplineMoveEffect;


	UPROPERTY(EditAnywhere, Category = "SplineMove")
	float m_MoveSpeed;

	// UI表示用コンポーネントを追加
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* m_InputPromptWidget;

	// エディタからセットする移動中の効果音
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SplineMove|Sound")
	USoundBase* m_SplineMoveSound;

	// 音を再生・停止制御するためのコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SplineMove|Sound")
	UAudioComponent* m_MoveAudioComponent;
private:

	bool m_RunningSplineMove;

	float m_CurrentDistance;
	float m_StartDistance;

	TWeakObjectPtr<AActor> m_CandidateActor;
	TWeakObjectPtr<AActor> m_MovingActor;
};
