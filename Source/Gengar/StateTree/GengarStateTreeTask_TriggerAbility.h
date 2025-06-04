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
UCLASS(DisplayName = "Trigger Ability Once (Gengar)")
class GENGAR_API UGengarStateTreeTask_TriggerAbility : public UStateTreeTaskBlueprintBase
{
    GENERATED_BODY()

public:
    explicit UGengarStateTreeTask_TriggerAbility(const FObjectInitializer& ObjectInitializer):
        UStateTreeTaskBlueprintBase(
            ObjectInitializer)
    {
        bShouldCopyBoundPropertiesOnTick = false;
        bShouldCopyBoundPropertiesOnExitState = false;
    }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Context")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowAbstract = false))
    TSubclassOf<UGameplayAbility> Ability;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FInstancedStruct ContextPayload;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Output)
    bool bAbilityEnded = false;

protected:
    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
                                           const FStateTreeTransitionResult& Transition) override;
    virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

    //
    UFUNCTION()
    void HandleAbilityEnded();
    UPROPERTY()
    FGengarAbilityEndedCallback Callback;
};
