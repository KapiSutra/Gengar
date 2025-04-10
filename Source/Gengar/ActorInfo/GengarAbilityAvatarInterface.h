// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GengarAbilityAvatarInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UGengarAbilityAvatarInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 
 */
class GENGAR_API IGengarAbilityAvatarInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, Category="Gengar Ability")
    USkeletalMeshComponent* AvatarAnimMeshComponent();
};
