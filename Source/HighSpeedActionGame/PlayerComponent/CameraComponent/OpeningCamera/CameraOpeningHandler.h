//担当
//伊藤直樹


//オープニングカメラを制御するハンドラ

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraOpeningHandler.generated.h"


class USpringArmComponent;
class UCameraComponent;
class APlayerController;
/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew)
class HIGHSPEEDACTIONGAME_API UCameraOpeningHandler : public UObject
{
	GENERATED_BODY()
public:
	void Initialize(USpringArmComponent* InSpringArm, UCameraComponent* InCamera, APlayerController* InPC);

	//演出開始
	void StartOpening(float WaitTime, float MoveDuration, float FaceDistance, float StartYawOffset);

	// 更新処理 (trueを返している間は演出中)
	bool UpdateOpening(float DeltaTime);

	// 強制終了
	void StopOpening();

	bool IsActive() const { return m_IsActive; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> OpeningWidgetClass;

	//移動開始からUIが消え始めるまでの時間
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Opening Settings")
	float UiHideDelayTime = 2.0f;
private:
	TWeakObjectPtr<USpringArmComponent> m_SpringArm;
	UPROPERTY()
	TWeakObjectPtr<APlayerController> m_PlayerController;

	bool m_IsActive;
	float m_CurrentTime;
	float m_MoveDuration;

	//パラメータキャッシュ
	//最終的な距離（通常の距離）
	float m_InitialArmLength;     
	//開始時の距離（顔アップ）
	float m_StartArmLength;       

	//最終的な回転
	FRotator m_InitialRotation;   
	//開始時の回転オフセット
	float m_StartYawOffset;       

	//顔の位置に合わせるためのオフセット
	FVector m_InitialSocketOffset;
	//顔の高さ（Z軸）へのオフセット
	FVector m_FaceSocketOffset;   

	//停止時間
	float m_WaitTime;

	//生成したWidgetを保持しておく変数
	UPROPERTY()
	UUserWidget* m_CreatedWidget;
	//UIを消したかどうかのフラグ
	bool m_IsUiHidden;
};
