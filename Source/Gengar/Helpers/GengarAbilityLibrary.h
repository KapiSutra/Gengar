// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Gengar/Effect/GengarGameplayEffectContext.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GengarAbilityLibrary.generated.h"

struct FGameplayAbilitySpecHandle;
struct FGameplayEventData;
/**
 * 
 */
UCLASS()
class GENGAR_API UGengarAbilityLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category="Gengar Ability")
    static void InitAbilityActorInfo(UAbilitySystemComponent* AbilitySystemComponent, AActor* Owner, AActor* Avatar);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability", meta=(ExpandBoolAsExecs="Valid"))
    static void GetGameplayEffectContext(const FGameplayEffectContextHandle& ContextHandle,
                                         FGengarGameplayEffectContext& Context,
                                         bool& Valid);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability")
    static void MakeEffectContextHandle(UAbilitySystemComponent* AbilitySystemComponent,
                                        const FInstancedStruct& Extra,
                                        FGameplayEffectContextHandle& Handle);

    UFUNCTION(BlueprintPure, Category="Gengar Ability")
    static FInstancedStruct TryGetEffectContextHandleExtra(const FGameplayEffectContextHandle& Handle);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability")
    static void SetEffectContextHandleExtra(FGameplayEffectContextHandle& Handle,
                                            const FInstancedStruct& Extra);

    UFUNCTION(BlueprintPure, Category="Gengar Ability")
    static FGameplayAbilitySpecHandle GetAbilitySpecHandleByClass(const UAbilitySystemComponent* AbilitySystemComponent,
                                                                  const TSubclassOf<UGameplayAbility>& AbilityClass);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability", meta=(AutoCreateRefTerm="EventData"))
    static bool ActivateAbilityWithGameplayEvent(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayAbilitySpecHandle& Handle, const FGameplayTag Tag,
                                                 const FGameplayEventData& EventData);

    UFUNCTION(BlueprintCallable, Category="Gengar Ability", meta=(AutoCreateRefTerm="EventData"))
    static bool ActivateAbilityByClassWithGameplayEvent(UAbilitySystemComponent* AbilitySystemComponent,
                                                        TSubclassOf<UGameplayAbility> AbilityClass,
                                                        const FGameplayTag Tag,
                                                        const FGameplayEventData& EventData);
};
