// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AmazingMouseRunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AMAZINGMOUSERUNNER_API AAmazingMouseRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
};
