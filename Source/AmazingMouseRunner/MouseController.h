// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MouseController.generated.h"

/**
 * 
 */
UCLASS()
class AMAZINGMOUSERUNNER_API AMouseController : public APlayerController
{
	GENERATED_BODY()

private:
	UUserWidget* GameHUD;
	UUserWidget* MenuHUD;
	UUserWidget* ShieldBar;

	FTimerHandle DeathTimerHandle;

	UPROPERTY()
	class UMouseGameInstance* GameInstance;
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> MenuHUDClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ShieldBarClass;

	void Death(int Score);
};
