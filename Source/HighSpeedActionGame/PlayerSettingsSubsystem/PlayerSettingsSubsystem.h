//担当：佐々木奏太
//プレイヤーの設定等を保存しておくゲームインスタンスサブシステム

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerSettingsSubsystem.generated.h"

/**
 *
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UPlayerSettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	void SetCameraSensitivity(float _sensitivity) { m_CameraSensitivity = _sensitivity; }
	float GetCameraSensitivity() { return m_CameraSensitivity; }
private:
	//カメラ感度
	float m_CameraSensitivity = 100.f;
};
