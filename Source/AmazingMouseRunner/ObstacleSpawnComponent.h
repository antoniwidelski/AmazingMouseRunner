// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObstacleSpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMAZINGMOUSERUNNER_API UObstacleSpawnComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	//If true dev can choose what element to spawn
	UPROPERTY(EditDefaultsOnly, Category = "a Platform", meta = (AllowPrivateAccess = "true"))
	bool CustomElements = false;

	UPROPERTY(EditDefaultsOnly, Category = "a Platform", meta=(EditCondition="CustomElements", AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> ElementsClasses;

	void SpawnElement();

	class ABasePlatform* Platform;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly)
	bool IsSpawnActive = true;
};
