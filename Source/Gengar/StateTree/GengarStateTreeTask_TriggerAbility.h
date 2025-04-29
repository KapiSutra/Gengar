// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Gengar/Helpers/GengarAbilityLibrary.h"

#include "GengarStateTreeTask_TriggerAbility.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;

/**
 * 
 */
UCLASS(DisplayName = "Trigger Ability (Gengar)")
class GENGAR_API UGengarStateTreeTask_TriggerAbility : public UStateTreeTaskBlueprintBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Context")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowAbstract = false))
    TSubclassOf<UGameplayAbility> Ability;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FInstancedStruct ContextPayload;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Output)
    bool bEnded = false;

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
                                           const FStateTreeTransitionResult& Transition) override;

    virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

protected:
    UFUNCTION()
    void HandleAbilityEnded();
};
