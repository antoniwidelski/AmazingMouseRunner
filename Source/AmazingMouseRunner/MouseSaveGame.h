// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MouseSaveGame.generated.h"

UCLASS()
class AMAZINGMOUSERUNNER_API UMouseSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Saved")
	int Coins = 0;

	UPROPERTY(EditAnywhere, Category = "Saved")
	int Shields = 0;

	UPROPERTY(EditAnywhere, Category = "Saved")
	int FenceType = 0;
	
	UPROPERTY(EditAnywhere, Category = "Saved")
	int ColorType = 0;

	UPROPERTY(EditAnywhere, Category = "Saved")
	bool StoneFenceLockState = false;
	UPROPERTY(EditAnywhere, Category = "Saved")
	bool MetalFenceLockState = false;

	UPROPERTY(EditAnywhere, Category = "Saved")
	bool RedLockState = false;
	UPROPERTY(EditAnywhere, Category = "Saved")
	bool SilverLockState = false;
	
	UPROPERTY(EditAnywhere, Category = "Saved")
	int BestScores[3];
};
