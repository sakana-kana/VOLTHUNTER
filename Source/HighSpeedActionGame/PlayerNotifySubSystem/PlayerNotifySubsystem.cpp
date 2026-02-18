// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerNotifySubsystem.h"

void UPlayerNotifySubsystem::NotifyJustEvasive(const AActor* Attacker)
{
	// ログ出力（確認用）
	UE_LOG(LogTemp, Log, TEXT("Subsystem: Just Evasive Notification Received!"));

	// 登録している全員（UIなど）に一斉送信
	if (OnJustEvasiveOccurred.IsBound())
	{
		OnJustEvasiveOccurred.Broadcast(Attacker);
	}
}

void UPlayerNotifySubsystem::NotifyPlayerDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Subsystem: Player Died Notification Received!"));

	if (OnPlayerDiedOccurred.IsBound())
	{
		OnPlayerDiedOccurred.Broadcast(DeadActor);
	}
}
