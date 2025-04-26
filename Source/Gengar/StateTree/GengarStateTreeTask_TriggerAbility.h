// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"

#include "GengarStateTreeTask_TriggerAbility.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS(DisplayName = "Trigger Ability (Gengar)")
class GENGAR_API UGengarStateTreeTask_TriggerAbility : public UStateTreeTaskBlueprintBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FInstancedStruct ContextPayload;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowAbstract = false))
    TSubclassOf<UGameplayAbility> Ability;

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
                                           const FStateTreeTransitionResult& Transition) override;
};
