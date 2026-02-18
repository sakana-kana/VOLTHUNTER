//’S“–
//ˆÉ“¡’¼Ž÷

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "../../AbilityPlayer_Base.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilityPlayer_AirAttackLight1.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSPEEDACTIONGAME_API UAbilityPlayer_AirAttackLight1 : public UAbilityPlayer_Base
{
	GENERATED_BODY()
	
	//UAbilityPlayer_AirAttackLight1();

	//virtual void InitializeTags()override;

    //
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

    // 
  
    virtual void OnMontageEnded()override;


};
