// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"

#include "GengarAbilitySystemGlobals.generated.h"

UCLASS()
class GENGAR_API UGengarAbilitySystemGlobals : public UAbilitySystemGlobals
{
    GENERATED_BODY()

    virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const override;
    virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
