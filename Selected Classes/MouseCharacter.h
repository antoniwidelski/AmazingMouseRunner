// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MouseCharacter.generated.h"

UCLASS()
class AMAZINGMOUSERUNNER_API AMouseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMouseCharacter();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* FeetPoint;

	float Speed;

	void MoveForward(float DeltaTime);

	//Mouse jump
	UFUNCTION(BlueprintCallable)
	void MJump();

	float ZeroLocation;

	//Sets location of mouse at the begining of the game
	void SetZeroLocation();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	float DownForce = 1;

	int FinalScore = 0;

	bool IsDead = false;

	bool IsDiving = false;

	//MouseCharacter starts diving
	UFUNCTION(BlueprintCallable)
	void Down();

	void Diving();

	int MultiCoinsHeld = 0;

	FTimerHandle MultiCoinTimerHandle;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	float MultiCoinRate = 0;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* StepSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* JumpSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* WhooshSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* CoinSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* ShieldSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	USoundBase* FlashSound;

	int DeathType;

	bool AlreadyEnemyJumped = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	FVector JumpVelocity;

	bool IsProtected = false;
	
	//Starts protection of mouse
	void Protection();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	float ProtectionTime = 10;

	float ProtectionTimeLeft;

	UFUNCTION(BlueprintPure)
	float GetProtectionTimePercentage();
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "aMouse")
	TSubclassOf<class ABasePlatform> BasePlatformClass;

	class UCharacterMovementComponent* MoveComp;

	//function for getting coins from enemies
	void AddNewMultiCoin();

	FTimerHandle MultiCoinsTimerHandle;

	//Function for double click
	UFUNCTION(BlueprintCallable)
	void Clicked();
	float SecondsWhileClicked = 0;

	bool CanDie = true;

	FTimerHandle CanDieQuickTimerHandle;

	class UMouseGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* ShieldWidget;

	UPROPERTY(EditAnywhere, Category = "aMouse")
	float SpeedAddition = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool GetIsJumping();

	void SpeedUp();

	UFUNCTION(BlueprintPure)
	int GetScore();

	void Death(int NewDeathType);

	UFUNCTION(Blueprintpure)
	bool GetIsDead();

	UFUNCTION(BlueprintPure)
	int GetFinalScore();

	UFUNCTION(BlueprintCallable)
	void PlayStepSound();

	//Killing enemy
	void EnemyJump();

	UFUNCTION(BlueprintPure)
	int GetDeathType();

	//Returns Z position of Mouse's feet
	float GetFeetZ();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEnemyJumpAnimation();

	void SetCanDieToTrue();

	UFUNCTION(BlueprintPure)
	bool GetIsProtected() { return IsProtected; }

	//Flash after hitting obstacle when character is protected
	UFUNCTION(BlueprintImplementableEvent)
	void Flash();
};

