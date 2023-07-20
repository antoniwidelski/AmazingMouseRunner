// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class AMAZINGMOUSERUNNER_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DeathBox;

	bool IsDead = false;

	class UCapsuleComponent* Cap;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aEnemy")
	USoundBase* DeathSound;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "aEnemy")
	USoundBase* MultiCoinSound;

protected:
	// Called when the game starts or when spawneds
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Triggers MouseCharacter's death
	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	//Triggers MouseCharacter's EnemyJump
	UFUNCTION()
	void OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintPure)
	bool GetIsDead();


};
