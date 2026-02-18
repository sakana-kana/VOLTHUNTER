// Fill out your copyright notice in the Description page of Project Settings.


#include "PostProsess.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/Actor.h"

// 探すタグの名前を定数にしておく（ミス防止）
const FName EFFECT_TAG_NAME = FName("PostProsess");

void UPostProsess::SetPostProsessActive(bool _Active)
{
	// Actorを取得（キャッシュにあればそれを使う）
	AActor* TargetActor = FindPostProsessActor();

	if (TargetActor)
	{
		// ポストプロセスコンポーネントを探して切り替える
		// (BPで追加したコンポーネントも、C++からは汎用クラスとして取得可能)
		if (UPostProcessComponent* PP = TargetActor->FindComponentByClass<UPostProcessComponent>())
		{
			PP->bEnabled = _Active;
		}
	}
}

AActor* UPostProsess::FindPostProsessActor()
{
	if (CachedEffectActor.IsValid())
	{
		return CachedEffectActor.Get();
	}

	UWorld* World = GetWorld();
	if (!World) return nullptr;

	//タグを使ってレベル内を検索する
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(World, EFFECT_TAG_NAME, FoundActors);

	if (FoundActors.Num() > 0)
	{
		// 見つかったらキャッシュする
		CachedEffectActor = FoundActors[0];
		return CachedEffectActor.Get();
	}

	// 見つからなかった場合
	UE_LOG(LogTemp, Warning, TEXT("ScreenEffectManager: Actor with tag 'BlackWhite' not found!"));
	return nullptr;
}
