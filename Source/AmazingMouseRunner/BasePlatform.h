// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.generated.h"

UCLASS()
class AMAZINGMOUSERUNNER_API ABasePlatform : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABasePlatform();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawnTrigger;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* DestroyTrigger;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* DeathTrigger;

	bool Triggered = false;

	//Draws type of platform
	void SetPlatformClass();
 
	TArray<AActor*> ChildElements;

	void DestroyElements();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Spawning next platform
	UFUNCTION()
	void SpawnOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//Destroying this platform
	UFUNCTION()
	void DestroyOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//Calling Player's death
	UFUNCTION()
	void DeathOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//Settings for spawning next platform
	UPROPERTY(EditAnywhere, Category = "a Platform")
	bool NextPlatformNotRandom = false;

	UPROPERTY(EditDefaultsOnly, Category = "a Platform", meta=(EditCondition = "NextPlatformNotRandom"))
	TSubclassOf<ABasePlatform> PlatformClass;

	UPROPERTY(EditAnywhere, Category = "a Platform")
	TArray<TSubclassOf<AActor>> ElementsClasses;

	TArray<TSubclassOf<AActor>> GetElementsClasses();

	void DestroyPlatformAndElements();

	void AddElement(AActor* Element);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	TArray<UMaterial*> Materials;

	UFUNCTION(BlueprintPure)
	UMaterial* GetPlatformMaterialByIndex(int Index);
};
