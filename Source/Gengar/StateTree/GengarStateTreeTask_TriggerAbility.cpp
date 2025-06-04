// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "GengarStateTreeTask_TriggerAbility.h"

#include "StateTreeExecutionContext.h"
#include "Gengar/Helpers/GengarAbilityLibrary.h"

EStateTreeRunStatus UGengarStateTreeTask_TriggerAbility::EnterState(FStateTreeExecutionContext& Context,
                                                                    const FStateTreeTransitionResult& Transition)
{
    const auto Result = Super::EnterState(Context, Transition);

    FGameplayEventData EventData;
    UGengarAbilityLibrary::MakeEffectContextHandle(AbilitySystemComponent, ContextPayload, EventData.ContextHandle);

    UGameplayAbility* OutAbilityInstance;

    this->Callback.BindDynamic(this, &ThisClass::HandleAbilityEnded);

    const auto bSuccess = UGengarAbilityLibrary::ActivateAbilityByClassWithEventData(
        AbilitySystemComponent, Ability,
        FGameplayTag::EmptyTag, EventData,
        OutAbilityInstance, Callback);

    if (!bSuccess)
    {
        bAbilityEnded = true;
        FinishTask();
    }

    return Result;
}

void UGengarStateTreeTask_TriggerAbility::ExitState(FStateTreeExecutionContext& Context,
                                                    const FStateTreeTransitionResult& Transition)
{
    Super::ExitState(Context, Transition);
}

void UGengarStateTreeTask_TriggerAbility::HandleAbilityEnded()
{
    bAbilityEnded = true;
    FinishTask();
}

EStateTreeRunStatus UGengarStateTreeTask_TriggerAbility::Tick(FStateTreeExecutionContext& Context,
    const float DeltaTime)
{
    return Super::Tick(Context, DeltaTime);
}
