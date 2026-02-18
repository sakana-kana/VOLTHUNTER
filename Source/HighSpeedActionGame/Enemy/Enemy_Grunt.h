//佐々木奏太担当
//雑魚敵クラス

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameplayTagContainer.h"
#include "Enemy_Grunt.generated.h"


/**
 *
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API AEnemy_Grunt : public AEnemyBase
{
	GENERATED_BODY()


public:

	AEnemy_Grunt();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetAIControllerIsActive(const bool _isActive)override;
	//ダメージヒットインターフェース
	virtual void TakeDamage(const FDamageInfo& _damageInfo)override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Grunt")
	float m_Timer;//汎用タイマー



};
