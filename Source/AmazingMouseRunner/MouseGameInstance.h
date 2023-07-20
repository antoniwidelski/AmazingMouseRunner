#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MouseGameInstance.generated.h"


UCLASS()
class AMAZINGMOUSERUNNER_API UMouseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AActor>> SkyTypes;

	AActor* Sky;

	UPROPERTY()
	class UMouseSaveGame* MouseSaveGame;
	FString SaveSlot = "Save4";

	int Coins= 0;
	int Shields = 0;

	int FenceType = 0;
	bool FenceLockState[3] = {true, false, false};
	int ColorType = 0;
	bool ColorLockState[3] = {true, false, false};

	int BestScores[4] = {0, 0, 0, 0};
	int MostRecentScore = 0;
	
public:
	UFUNCTION(BlueprintCallable)
	void LoadGame();
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintPure)
	int GetCoins() { return Coins; }
	UFUNCTION(BlueprintPure)
	int GetShields() { return Shields; }

	UFUNCTION(BlueprintPure)
	int GetFenceType() { return FenceType; }
	UFUNCTION(BlueprintPure)
	int GetColorType() { return ColorType; }

	UFUNCTION(BlueprintCallable)
	void SetFenceType(int NewType) { FenceType = NewType; }
	UFUNCTION(BlueprintCallable)
	void SetColorType(int NewType) { ColorType = NewType; SetSky(); }

	UFUNCTION(BlueprintCallable)
	bool IsFenceUnlocked(int FenceID);
	UFUNCTION(BlueprintCallable)
	bool IsColorUnlocked(int ColorID);

	void AddCoin() { Coins++; }
	void RemoveShield() { Shields--; }

	//Shop functions
	UFUNCTION(BlueprintCallable)
	void ItemClicked(FString Type, int Place, int Cost);
	bool Shop(int ShopID, int Cost);
	UFUNCTION(BlueprintImplementableEvent)
	void NotEnoughMoney();
	
	UFUNCTION(BlueprintCallable)
	void SetSky();
	
	//Score Functions
	UFUNCTION(BlueprintCallable)
	bool SortScores();
	UFUNCTION(BlueprintCallable)
	void SetMostRecentScore(int Score) { MostRecentScore = Score; }
	UFUNCTION(BlueprintPure)
	int GetBestScoreByPlace(int Place) { return BestScores[Place-1]; }

	
};
