//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "PostProcess.h"
//
//// Sets default values for this component's properties
//UPostProcess::UPostProcess()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}
//
//
//// Called when the game starts
//void UPostProcess::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
//void UPostProcess::PlayPostProcess(FName EffectKey, float Duration)
//{
//	// 指定されたキーに対応するクラスがBPで登録されているか確認
//	if (!m_EffectClasses.Contains(EffectKey))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("PostProcess: Key '%s' is not registered in BP!"), *EffectKey.ToString());
//		return;
//	}
//
//	TSubclassOf<AActor> TargetClass = m_EffectClasses[EffectKey];
//	if (!TargetClass) return;
//
//	AActor* Owner = GetOwner();
//	if (!Owner) return;
//
//	StopPostProcess(EffectKey);
//
//	// 生成処理
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Owner = Owner;
//	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//	AActor* NewPPActor = GetWorld()->SpawnActor<AActor>(
//		TargetClass,
//		Owner->GetActorLocation(),
//		FRotator::ZeroRotator,
//		SpawnParams
//	);
//
//	if (NewPPActor)
//	{
//		// プレイヤーに追従させる
//		NewPPActor->AttachToActor(Owner, FAttachmentTransformRules::KeepWorldTransform);
//
//		// 管理マップに追加
//		m_ActiveEffects.Add(EffectKey, NewPPActor);
//
//		// 秒数指定がある場合、タイマーをセット
//		if (Duration > 0.f)
//		{
//			FTimerHandle TimerHandle;
//			FTimerDelegate TimerDel;
//			TimerDel.BindUObject(this, &UPostProcess::OnPostProcessExpired, EffectKey);
//
//			GetWorld()->GetTimerManager().SetTimer(
//				TimerHandle,
//				TimerDel,
//				Duration,
//				false
//			);
//
//			m_ActiveTimers.Add(EffectKey, TimerHandle);
//		}
//	}
//}
//void UPostProcess::StopPostProcess(FName EffectKey)
//{
//	if (m_ActiveEffects.Contains(EffectKey))
//	{
//		AActor* PPActor = m_ActiveEffects[EffectKey];
//		if (IsValid(PPActor))
//		{
//			PPActor->Destroy();
//		}
//		m_ActiveEffects.Remove(EffectKey);
//	}
//
//	// タイマーのクリア
//	if (m_ActiveTimers.Contains(EffectKey))
//	{
//		GetWorld()->GetTimerManager().ClearTimer(m_ActiveTimers[EffectKey]);
//		m_ActiveTimers.Remove(EffectKey);
//	}
//}
//
//void UPostProcess::OnPostProcessExpired(FName EffectKey)
//{
//	StopPostProcess(EffectKey);
//}
//
