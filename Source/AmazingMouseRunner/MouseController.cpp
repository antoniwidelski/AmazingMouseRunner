// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MouseGameInstance.h"

void AMouseController::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = Cast<UMouseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    GameHUD = CreateWidget(this, GameHUDClass);
    ShieldBar = CreateWidget(this, ShieldBarClass);
    if(GameHUD != nullptr)
    {
        GameHUD->AddToViewport();
    }
    if(ShieldBar != nullptr)
    {
        ShieldBar->AddToViewport();
    }
}

void AMouseController::Death(int Score)
{
    if(GameInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("Game Instance valid!"));
        GameInstance->SetMostRecentScore(Score);
        GameInstance->SaveGame();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Game Instance invalid!"));
    }

    GameHUD = CreateWidget(this, GameHUDClass);
    if(GameHUD != nullptr)
    {
        GameHUD->RemoveFromParent();
    }

    MenuHUD = CreateWidget(this, MenuHUDClass);
    if(MenuHUD != nullptr)
    {
        MenuHUD->AddToViewport();
    }
}