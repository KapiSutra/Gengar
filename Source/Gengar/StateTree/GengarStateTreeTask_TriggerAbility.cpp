// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "GengarStateTreeTask_TriggerAbility.h"

#include "Gengar/Helpers/GengarAbilityLibrary.h"

EStateTreeRunStatus UGengarStateTreeTask_TriggerAbility::EnterState(FStateTreeExecutionContext& Context,
                                                                    const FStateTreeTransitionResult& Transition)
{
    const auto Result = Super::EnterState(Context, Transition);

    FGameplayEventData EventData;
    UGengarAbilityLibrary::MakeEffectContextHandle(AbilitySystemComponent, ContextPayload, EventData.ContextHandle);

    UGameplayAbility* OutAbilityInstance;

    FGengarAbilityEndedCallback AbilityEndedCallback{};
    AbilityEndedCallback.BindDynamic(this, &ThisClass::HandleAbilityEnded);

    const auto bSuccess = UGengarAbilityLibrary::ActivateAbilityByClassWithGameplayEvent(
        AbilitySystemComponent, Ability,
        FGameplayTag::EmptyTag, EventData,
        OutAbilityInstance, AbilityEndedCallback);

    if (!bSuccess)
    {
        FinishTask();
    }

    return Result;
}

void UGengarStateTreeTask_TriggerAbility::HandleAbilityEnded()
{
    FinishTask();
}
