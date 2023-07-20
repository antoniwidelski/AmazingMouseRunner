// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlatform.h"
#include "MouseGameInstance.h"

void ARunGameMode::StartPlay()
{
    Super::StartPlay();

    UMouseGameInstance* GameInstance = Cast<UMouseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if(GameInstance) GameInstance->SetSky();   
}

TArray<TSubclassOf<class ABasePlatform>> ARunGameMode::GetPlatformTypes()
{
     return PlatformTypes;
}

void ARunGameMode::DestroyPlatforms()
{
    UE_LOG(LogTemp, Warning, TEXT("Destroying All Platforms..."));

    TArray<AActor*> Platforms;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePlatform::StaticClass(), Platforms);

    int Number = Platforms.Num();

    if (Number <= 0) return;

    for (int i = 0; i <= Number-1; i++)
    {
        UE_LOG(LogTemp, Warning, TEXT("Destroying Platform Number: %i"), i);
        ABasePlatform* Platform = Cast<ABasePlatform>(Platforms[i]);
        if(Platform)
        {   
            UE_LOG(LogTemp, Warning, TEXT("And It Exists: %s"), *Platform->GetName());
            Platform->DestroyPlatformAndElements();
        }
    }
}



