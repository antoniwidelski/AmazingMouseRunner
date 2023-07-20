#include "MouseGameInstance.h"
#include "MouseSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "MouseGameInstance.h"

void UMouseGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Error, TEXT("MouseGameInstace Initialisation..."));

    MouseSaveGame = Cast<UMouseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));

    if(MouseSaveGame == nullptr)
    {
        //UE_LOG(LogTemp, Error, TEXT("Creating new save..."));
        MouseSaveGame = Cast<UMouseSaveGame>(UGameplayStatics::CreateSaveGameObject(UMouseSaveGame::StaticClass()));

        MouseSaveGame->Coins = 0;
        MouseSaveGame->Shields = 0;
        MouseSaveGame->FenceType = 0;
        MouseSaveGame->ColorType = 0;

        MouseSaveGame->StoneFenceLockState = false;
        MouseSaveGame->MetalFenceLockState = false;
        MouseSaveGame->RedLockState = false;
        MouseSaveGame->SilverLockState = false;

        MouseSaveGame->BestScores[0] = 0;
        MouseSaveGame->BestScores[1] = 0;
        MouseSaveGame->BestScores[2] = 0;

        UGameplayStatics::SaveGameToSlot(MouseSaveGame, SaveSlot, 0);
    }
    LoadGame();
}

void UMouseGameInstance::LoadGame()
{
    Coins = MouseSaveGame->Coins;
    Shields = MouseSaveGame->Shields;

    FenceType = MouseSaveGame->FenceType;
    ColorType = MouseSaveGame->ColorType;

    FenceLockState[1] = MouseSaveGame->StoneFenceLockState;
    FenceLockState[2] = MouseSaveGame->MetalFenceLockState;
    ColorLockState[1] = MouseSaveGame->RedLockState;
    ColorLockState[2] = MouseSaveGame->SilverLockState;

    BestScores[0] = MouseSaveGame->BestScores[0];
    BestScores[1] = MouseSaveGame->BestScores[1];
    BestScores[2] = MouseSaveGame->BestScores[2];
    BestScores[3] = 0;

    //UE_LOG(LogTemp, Error, TEXT("Score from save: %i"), MouseSaveGame->BestScores[0]);
    //UE_LOG(LogTemp, Error, TEXT("Score from game instance: %i"), BestScores[0]);
}

void UMouseGameInstance::SaveGame()
{
    MouseSaveGame = Cast<UMouseSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));

    if(MouseSaveGame)
    {
        //UE_LOG(LogTemp, Error, TEXT("Saving game..."));

        MouseSaveGame->Coins = Coins;
        MouseSaveGame->Shields = Shields;

        MouseSaveGame->FenceType = FenceType;
        MouseSaveGame->ColorType = ColorType;

        MouseSaveGame->StoneFenceLockState = FenceLockState[1];
        MouseSaveGame->MetalFenceLockState = FenceLockState[2];
        MouseSaveGame->RedLockState = ColorLockState[1];
        MouseSaveGame->SilverLockState = ColorLockState[2];

        MouseSaveGame->BestScores[0] = BestScores[0];
        MouseSaveGame->BestScores[1] = BestScores[1];
        MouseSaveGame->BestScores[2] = BestScores[2];

        UGameplayStatics::SaveGameToSlot(MouseSaveGame, SaveSlot, 0);

        UE_LOG(LogTemp, Error, TEXT("Score from save: %i"), MouseSaveGame->BestScores[0]);
        UE_LOG(LogTemp, Error, TEXT("Score from game instance: %i"), BestScores[0]);
    }
    else
    {
        //UE_LOG(LogTemp, Error, TEXT("MouseSaveGame invalid!"));
    }
}

void UMouseGameInstance::ItemClicked(FString Type, int Place, int Cost)
{
    if(Type == "S")
    {
        Shop(0, Cost);
    }
    else if(Type == "F")
    {
        if(FenceLockState[Place-1])
        {
           SetFenceType(Place-1);
        }
        else
        {
            Shop(Place-1, Cost);
        }
    }
    else if(Type == "C")
    {
        if(ColorLockState[Place-1])
        {
            SetColorType(Place-1);
        }
        else
        {
            Shop(Place+1, Cost);
        }
    }
}

bool UMouseGameInstance::Shop(int ShopID, int Cost)
{
    if(Coins<Cost)
    {
        NotEnoughMoney();
        return false;
    }
    else
    {
        switch(ShopID)
        {
            case 0:
                Shields++;
                break;
            case 1:
                FenceLockState[1] = true;
                break;
            case 2:
                FenceLockState[2] = true;
                break;
            case 3:
                ColorLockState[1] = true;
                break;
            case 4:
                ColorLockState[2] = true;
                break;
        }
        Coins-=Cost;
        return true;
    }   
}

bool UMouseGameInstance::IsFenceUnlocked(int FenceID)
{
    return FenceLockState[FenceID];
}

bool UMouseGameInstance::IsColorUnlocked(int ColorID)
{
    return ColorLockState[ColorID];
}

void UMouseGameInstance::SetSky()
{
    if(Sky)
    {
        Sky->Destroy();
    }

    UWorld* World = GetWorld();
    if(World) Sky = GetWorld()->SpawnActor<AActor>(SkyTypes[ColorType], FVector(0, 0, -701164), FRotator(0, 0, 0));
}

bool UMouseGameInstance::SortScores()
{
    int BestScore = BestScores[0];
    BestScores[3] = MostRecentScore;

    for(int i = 0; i < 4; i++)
    {
        for(int j = i + 1; j < 4; j++)
        {
            if(BestScores[j] > BestScores[i])
            {
                int temp = BestScores[i];
                BestScores[i] = BestScores[j];
                BestScores[j] = temp;
            }
        }
    }
    
    for(int n = 0; n < 4; n++)
    {
        UE_LOG(LogTemp, Error, TEXT("%i. %i"), n, BestScores[n]);
    }
    
    UE_LOG(LogTemp, Error, TEXT("BestScore: %i, Score: %i"), BestScore, BestScores[0]);
    if(BestScore != BestScores[0])
    {
        return true;
    }
    return false;
}

