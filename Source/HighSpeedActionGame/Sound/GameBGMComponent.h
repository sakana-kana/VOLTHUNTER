// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameBGMComponent.generated.h"

class USoundBase;
class UAudioComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HIGHSPEEDACTIONGAME_API UGameBGMComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UGameBGMComponent();


    // --- åƒÇ—èoÇµóp ---
    UFUNCTION(BlueprintCallable, Category = "BGM")
    void PlayNormalBGM();

    UFUNCTION(BlueprintCallable, Category = "BGM")
    void PlayBossBGM();

    UFUNCTION(BlueprintCallable, Category = "BGM")
    void PlayClearBGM();

    UFUNCTION(BlueprintCallable, Category = "BGM")
    void StopBGM();

    // --- BPÇ≈ê›íËÇ∑ÇÈâπåπ ---
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BGM")
    USoundBase* NormalBGM;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BGM")
    USoundBase* BossBGM;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BGM")
    USoundBase* ClearBGM;

private:
    // ì‡ïîèàóù
    void PlayBGM(USoundBase* NewSound);

    UPROPERTY()
    UAudioComponent* CurrentAudioComponent;
};
