// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "GengarAbilityLibrary.h"

#include "AbilitySystemComponent.h"

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
                                                    const FInstancedStruct& Extra,
                                                    FGameplayEffectContextHandle& Handle)
{
    Handle = AbilitySystemComponent->MakeEffectContext();
    SetEffectContextHandleExtra(Handle, Extra);
}

FInstancedStruct UGengarAbilityLibrary::TryGetEffectContextHandleExtra(const FGameplayEffectContextHandle& Handle)
{
    bool bValid = false;
    FGengarGameplayEffectContext Context;
    GetGameplayEffectContext(Handle, Context, bValid);

    if (bValid)
    {
        return Context.Extra;
    }

    return {};
}

FGameplayEffectContextHandle UGengarAbilityLibrary::SetEffectContextHandleExtra(FGameplayEffectContextHandle& Handle,
    const FInstancedStruct& Extra)
{
    auto* Context = Handle.Get();
    if (auto* GengarContext = static_cast<FGengarGameplayEffectContext*>(Context))
    {
        GengarContext->Extra = Extra;
    }
    return Handle;
}

FGameplayAbilitySpecHandle UGengarAbilityLibrary::GetAbilitySpecHandleByClass(
    const UAbilitySystemComponent* AbilitySystemComponent,
    const TSubclassOf<UGameplayAbility>&
    AbilityClass)
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
                                                             const FGameplayEventData& EventData)
{
    if (!ensure(AbilitySystemComponent))
    {
        return false;
    }

    return AbilitySystemComponent->TriggerAbilityFromGameplayEvent(
        Handle, AbilitySystemComponent->AbilityActorInfo.Get(), Tag, &EventData,
        *AbilitySystemComponent);
}

bool UGengarAbilityLibrary::ActivateAbilityByClassWithGameplayEvent(UAbilitySystemComponent* AbilitySystemComponent,
                                                                    const TSubclassOf<UGameplayAbility> AbilityClass,
                                                                    const FGameplayTag Tag,
                                                                    const FGameplayEventData& EventData)
{
    return ActivateAbilityWithGameplayEvent(AbilitySystemComponent,
                                            GetAbilitySpecHandleByClass(AbilitySystemComponent, AbilityClass), Tag,
                                            EventData);
}
