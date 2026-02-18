// 佐々木奏太担当
//ボス敵（トロイの木馬）クラス

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Enemy_TrojanHorseBoss.generated.h"

class UBoxComponent;

/**
 * 
 */

UCLASS()
class HIGHSPEEDACTIONGAME_API AEnemy_TrojanHorseBoss : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemy_TrojanHorseBoss();
	virtual void TakeDamage(const FDamageInfo& _damageInfo)override;
	void Tick(float DeltaTime)override;
protected:
	// 胴体用のBoxコリジョンコンポーネント
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* BodyBox;
};
