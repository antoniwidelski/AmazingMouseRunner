// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawnComponent.h"
#include "BasePlatform.h"

// Called when the game starts
void UObstacleSpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(CustomElements == false)
	{
		Platform = Cast<ABasePlatform>(GetOwner());

		if (Platform == nullptr) return;

		ElementsClasses = Platform->GetElementsClasses();
	}
	SpawnElement();
}

void UObstacleSpawnComponent::SpawnElement()
{
	if (ElementsClasses.Num() == 0) return;

	UE_LOG(LogTemp, Warning, TEXT("Spawning Element.."));

	int random = (rand() % ElementsClasses.Num());

	AActor* Element = GetWorld()->SpawnActor<AActor>(ElementsClasses[random], GetComponentLocation(), FRotator(0, 0, 0));

	if(Platform != nullptr) Platform->AddElement(Element);
}