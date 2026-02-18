//佐々木奏太担当
//ワールドセッティングクラス

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MyWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API AMyWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool m_UseEnemyManager = true;


	UPROPERTY(EditAnywhere)
	bool m_GameplayAreaEventManager = true;

	UPROPERTY(EditAnywhere)
	bool m_AttackCollisionPool = true;
};
