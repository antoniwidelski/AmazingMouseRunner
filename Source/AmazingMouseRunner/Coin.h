// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class AMAZINGMOUSERUNNER_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Coin")
	USoundBase* CoinSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Coin")
	float MoveOffset = 0;

	//Spinning Coin
	void Spin(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float SpinSpeed = 0;

	bool CanCollect = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Collecting Coin
	UFUNCTION()
	void Overlapped(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
