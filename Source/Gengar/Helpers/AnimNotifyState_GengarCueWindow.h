// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "AnimNotifyState_GengarCueWindow.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Cue Window (Gengar)")
class GENGAR_API UAnimNotifyState_GengarCueWindow : public UAnimNotify_PlayMontageNotifyWindow
{
    GENERATED_BODY()

    UAnimNotifyState_GengarCueWindow()
    {
        NotifyName = "Cue Window (Gengar)";
    }

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(Categories="GameplayCue"), Category="Gameplay Cue")
    FGameplayTag GameplayCueTag;
};
