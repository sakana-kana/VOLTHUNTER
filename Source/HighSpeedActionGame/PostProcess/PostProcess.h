//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "PostProcess.generated.h"
//
//
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class HIGHSPEEDACTIONGAME_API UPostProcess : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:	
//	// Sets default values for this component's properties
//	UPostProcess();
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//
//	
//	// ポストプロセスアクターを生成する
//	// EffectKey     管理用のキー（例: "Skill", "JustEvasion"）
//	// Duration      表示時間（0以下なら手動で消すまで永続）
//	
//	UFUNCTION(BlueprintCallable, Category = "PostProcess")
//	void PlayPostProcess(FName EffectKey,float Duraction = -1.f);
//
//	//指定したキーのポストプロセスを削除する
//	UFUNCTION(BlueprintCallable, Category = "PostProcess")
//	void StopPostProcess(FName EffectKey);
//
//private:
//	// 内部処理用：タイマーで削除する
//	void OnPostProcessExpired(FName EffectKey);
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PostProcess Config")
//	TMap<FName, TSubclassOf<AActor>> m_EffectClasses;
//private:
//	// 現在アクティブなエフェクトを管理するマップ <キー, 生成されたActor>
//	UPROPERTY()
//	TMap<FName, AActor*> m_ActiveEffects;
//
//	// タイマーハンドル管理用
//	TMap<FName, FTimerHandle> m_ActiveTimers;
//};
