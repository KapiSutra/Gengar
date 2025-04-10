// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "GengarAbilitySystemGlobals.h"

FGameplayAbilityActorInfo* UGengarAbilitySystemGlobals::AllocAbilityActorInfo() const
{
    return Super::AllocAbilityActorInfo();
}

FGameplayEffectContext* UGengarAbilitySystemGlobals::AllocGameplayEffectContext() const
{
    return Super::AllocGameplayEffectContext();
}
