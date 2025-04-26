// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "GengarGameplayEffectContext.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct GENGAR_API FGengarGameplayEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FInstancedStruct Payload;

    virtual UScriptStruct* GetScriptStruct() const override
    {
        return StaticStruct();
    };

    virtual FGameplayEffectContext* Duplicate() const override
    {
        FGengarGameplayEffectContext* Context = new FGengarGameplayEffectContext();
        *Context = *this;
        Context->Payload = Payload;
        return Context;
    };

    virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override
    {
        return Super::NetSerialize(Ar, Map, bOutSuccess) && Payload.NetSerialize(Ar, Map, bOutSuccess);
    };
};


template <>
struct TStructOpsTypeTraits<FGengarGameplayEffectContext> : TStructOpsTypeTraitsBase2<FGengarGameplayEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true,
    };
};
