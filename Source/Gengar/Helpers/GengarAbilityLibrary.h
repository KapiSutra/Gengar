﻿// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gengar/Effect/GengarGameplayEffectContext.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GengarAbilityLibrary.generated.h"

struct FGameplayAbilitySpecHandle;
struct FGameplayEventData;

DECLARE_DYNAMIC_DELEGATE(FGengarAbilityEndedCallback);

/**
 * 
 */
UCLASS()
class GENGAR_API UGengarAbilityLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Gengar Ability")
    static void InitAbilityActorInfo(UAbilitySystemComponent* AbilitySystemComponent, AActor* Owner, AActor* Avatar,
                                     APlayerController* PlayerController);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability", meta=(ExpandBoolAsExecs="Valid"))
    static void GetGameplayEffectContext(const FGameplayEffectContextHandle& ContextHandle,
                                         FGengarGameplayEffectContext& Context,
                                         bool& Valid);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability")
    static void MakeEffectContextHandle(UAbilitySystemComponent* AbilitySystemComponent,
                                        const FInstancedStruct& Payload,
                                        FGameplayEffectContextHandle& Handle);

    UFUNCTION(BlueprintPure, Category="Gengar Ability")
    static FInstancedStruct TryGetEffectContextPayload(const FGameplayEffectContextHandle& Handle);

    UFUNCTION(BlueprintPure, Category="Gengar Ability", meta=(DefaultToSelf="Ability"))
    static void GetAbilityContextPayload(const UGameplayAbility* Ability, FInstancedStruct& Payload);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability")
    static void SetEffectContextPayload(FGameplayEffectContextHandle& Handle,
                                        const FInstancedStruct& Payload);

    UFUNCTION(BlueprintPure, Category="Gengar Ability")
    static FGameplayAbilitySpecHandle FindAbilitySpecHandleByClass(
        const UAbilitySystemComponent* AbilitySystemComponent,
        const TSubclassOf<UGameplayAbility>& AbilityClass);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability", meta=(AutoCreateRefTerm="EventData", CPP_Default_OnEnded))
    static bool ActivateAbilityWithEventData(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayAbilitySpecHandle& Handle, const FGameplayTag Tag,
                                             const FGameplayEventData& EventData,
                                             UGameplayAbility*& AbilityInstance,
                                             FGengarAbilityEndedCallback OnEnded = FGengarAbilityEndedCallback());

    UFUNCTION(BlueprintCallable, Category="Gengar Ability", meta=(AutoCreateRefTerm="EventData", CPP_Default_OnEnded))
    static bool ActivateAbilityByClassWithEventData(UAbilitySystemComponent* AbilitySystemComponent,
                                                    TSubclassOf<UGameplayAbility> AbilityClass,
                                                    const FGameplayTag Tag,
                                                    const FGameplayEventData& EventData,
                                                    UGameplayAbility*& AbilityInstance,
                                                    FGengarAbilityEndedCallback OnEnded =
                                                        FGengarAbilityEndedCallback());
};
