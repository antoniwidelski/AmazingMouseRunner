// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmazingMouseRunnerGameModeBase.h"
#include "RunGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AMAZINGMOUSERUNNER_API ARunGameMode : public AAmazingMouseRunnerGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void StartPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "a Platform")
	TArray<TSubclassOf<class ABasePlatform>> PlatformTypes;

public:
	//returns list of possible platforms
	TArray<TSubclassOf<class ABasePlatform>> GetPlatformTypes();

	//Destroying all platforms
	void DestroyPlatforms();
};
