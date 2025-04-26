// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "GengarAbilityLibrary.h"

#include "AbilitySystemComponent.h"

void UGengarAbilityLibrary::InitAbilityActorInfo(UAbilitySystemComponent* AbilitySystemComponent, AActor* Owner,
                                                 AActor* Avatar)
{
    AbilitySystemComponent->InitAbilityActorInfo(Owner, Avatar);
}

void UGengarAbilityLibrary::GetGameplayEffectContext(const FGameplayEffectContextHandle& ContextHandle,
                                                     FGengarGameplayEffectContext& Context,
                                                     bool& Valid)
{
    if (ContextHandle.IsValid())
    {
        Context = *static_cast<const FGengarGameplayEffectContext*>(ContextHandle.Get());
        Valid = true;
    }
}

void UGengarAbilityLibrary::MakeEffectContextHandle(UAbilitySystemComponent* AbilitySystemComponent,
                                                    const FInstancedStruct& Payload,
                                                    FGameplayEffectContextHandle& Handle)
{
    Handle = AbilitySystemComponent->MakeEffectContext();
    SetEffectContextPayload(Handle, Payload);
}

FInstancedStruct UGengarAbilityLibrary::TryGetEffectContextPayload(const FGameplayEffectContextHandle& Handle)
{
    bool bValid = false;
    FGengarGameplayEffectContext Context;
    GetGameplayEffectContext(Handle, Context, bValid);

    if (bValid)
    {
        return Context.Payload;
    }

    return {};
}

void UGengarAbilityLibrary::GetAbilityContextPayload(const UGameplayAbility* Ability,
                                                     FInstancedStruct& Payload)
{
    const auto EventDataProperty = UGameplayAbility::StaticClass()->FindPropertyByName("CurrentEventData");
    FGameplayEventData CurrentEventData;
    EventDataProperty->GetValue_InContainer(Ability, &CurrentEventData);

    FGengarGameplayEffectContext Context;
    bool bValid;
    GetGameplayEffectContext(CurrentEventData.ContextHandle, Context, bValid);
    if (bValid)
    {
        Payload = Context.Payload;
    }
}

void UGengarAbilityLibrary::SetEffectContextPayload(FGameplayEffectContextHandle& Handle,
                                                    const FInstancedStruct& Payload)
{
    auto* Context = Handle.Get();
    if (auto* GengarContext = static_cast<FGengarGameplayEffectContext*>(Context))
    {
        GengarContext->Payload = Payload;
    }
}

FGameplayAbilitySpecHandle UGengarAbilityLibrary::GetAbilitySpecHandleByClass(
    const UAbilitySystemComponent* AbilitySystemComponent,
    const TSubclassOf<UGameplayAbility>& AbilityClass)
{
    for (auto&& Spec : AbilitySystemComponent->GetActivatableAbilities())
    {
        if (Spec.Ability == AbilityClass.GetDefaultObject())
        {
            return Spec.Handle;
        }
    }

    return FGameplayAbilitySpecHandle();
}

bool UGengarAbilityLibrary::ActivateAbilityWithGameplayEvent(UAbilitySystemComponent* AbilitySystemComponent,
                                                             const FGameplayAbilitySpecHandle& Handle,
                                                             const FGameplayTag Tag,
                                                             const FGameplayEventData& EventData,
                                                             UGameplayAbility*& AbilityInstance,
                                                             FGengarAbilityEndedCallback OnEnded)
{
    if (!ensure(AbilitySystemComponent))
    {
        return false;
    }

    // return AbilitySystemComponent->TriggerAbilityFromGameplayEvent(
    //     Handle,
    //     AbilitySystemComponent->AbilityActorInfo.Get(),
    //     Tag,
    //     &EventData,
    //     *AbilitySystemComponent);

    auto Delegate = FOnGameplayAbilityEnded::FDelegate::CreateLambda(
        [OnEnded](UGameplayAbility*)
        {
            OnEnded.ExecuteIfBound();
        });

    return AbilitySystemComponent->InternalTryActivateAbility(
        Handle, AbilitySystemComponent->GetPredictionKeyForNewAction(),
        &AbilityInstance,
        &Delegate, &EventData);
}

bool UGengarAbilityLibrary::ActivateAbilityByClassWithGameplayEvent(UAbilitySystemComponent* AbilitySystemComponent,
                                                                    const TSubclassOf<UGameplayAbility> AbilityClass,
                                                                    const FGameplayTag Tag,
                                                                    const FGameplayEventData& EventData,
                                                                    UGameplayAbility*& AbilityInstance,
                                                                    const FGengarAbilityEndedCallback OnEnded)
{
    UGameplayAbility* OutInstance;
    return ActivateAbilityWithGameplayEvent(AbilitySystemComponent,
                                            GetAbilitySpecHandleByClass(AbilitySystemComponent, AbilityClass),
                                            Tag,
                                            EventData, OutInstance, OnEnded);
}
