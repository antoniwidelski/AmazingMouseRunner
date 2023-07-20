// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MouseController.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlatform.h"
#include "RunGameMode.h"
#include "MouseGameInstance.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMouseCharacter::AMouseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	FeetPoint = CreateDefaultSubobject<USceneComponent>(TEXT("FeetPoint"));
	FeetPoint->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	ShieldWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Shield"));
	ShieldWidget->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AMouseCharacter::BeginPlay()
{
	Super::BeginPlay();

	FVector Location = GetActorLocation();
	Location.Y = 0;
	SetActorLocation(Location);
	SetZeroLocation();

	MoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());

	GameInstance = Cast<UMouseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called every frame
void AMouseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsDead) return;

	MoveForward(DeltaTime);
	Diving();

	if(AlreadyEnemyJumped)
	{
		if(MoveComp)
		{
			if(MoveComp->IsFalling() == true)
			{
				AlreadyEnemyJumped = false;
			}
		}
	}

	if(ProtectionTimeLeft<=0)
	{
		IsProtected = false;
	}
	else
	{
		ProtectionTimeLeft-=DeltaTime;
	}
}

// Called to bind functionality to input
void AMouseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMouseCharacter::MJump);
	PlayerInputComponent->BindAction(TEXT("Down"), IE_Pressed, this, &AMouseCharacter::Down);
	PlayerInputComponent->BindAction(TEXT("Protection"), IE_Pressed, this, &AMouseCharacter::Clicked);
}

void AMouseCharacter::MoveForward(float DeltaTime)
{
	AddMovementInput(GetActorForwardVector());
}

void AMouseCharacter::MJump()
{
	if(IsDead || GetIsJumping()) return;

	Super::Jump();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSound, GetActorLocation(), FRotator(0, 0, 0));

	SecondsWhileClicked = 0;
}

void AMouseCharacter::SetZeroLocation()
{
	ZeroLocation = GetActorLocation().X;
}

void AMouseCharacter::Down()
{
	IsDiving = true;
	UE_LOG(LogTemp, Warning, TEXT("Diving..."));
	if(MoveComp == nullptr) return;
	if(MoveComp->IsFalling())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WhooshSound, GetActorLocation(), FRotator(0, 0, 0));
	}
	SecondsWhileClicked = 0;
}

void AMouseCharacter::Diving()
{
	if(IsDiving && GetMovementComponent()->IsFalling())
	{
		GetRootComponent()->AddLocalOffset(FVector(0, 0, -DownForce));
	}
	else if(IsDiving)
	{
		IsDiving = false;
	}
}

void AMouseCharacter::Clicked()
{
	if(IsProtected) return;

	float TimePassed = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	if(SecondsWhileClicked == 0 || TimePassed - SecondsWhileClicked >= 1)
	{
		SecondsWhileClicked = TimePassed;
	}
	else
	{
		SecondsWhileClicked = 0;
		
		if(GameInstance)
		{
			int Shields = GameInstance->GetShields();
			if(Shields > 0)
			{
				GameInstance->RemoveShield();
				IsProtected = true;
				ProtectionTimeLeft = ProtectionTime;

				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShieldSound, GetActorLocation(), FRotator(0, 0, 0));

				UE_LOG(LogTemp, Warning, TEXT("Protecting..."));
			}
		}
	}
}

void AMouseCharacter::Protection()
{
	Flash();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FlashSound, GetActorLocation(), FRotator(0, 0, 0));

	ARunGameMode* GameMode = Cast<ARunGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if(GameMode != nullptr)
	{
		GameMode->DestroyPlatforms();
	}

	CanDie = false;
	GetWorldTimerManager().SetTimer(CanDieQuickTimerHandle, this, &AMouseCharacter::SetCanDieToTrue, 1);

	FVector NewLocation = GetActorLocation();
	NewLocation.Y -= 2000;
	SetActorLocation(NewLocation);

	FVector PlatformLocation(NewLocation.X, NewLocation.Y, 0);
	GetWorld()->SpawnActor<ABasePlatform>(BasePlatformClass, PlatformLocation, FRotator(0, 0, 0));

	PlatformLocation.X += 1000;
	GetWorld()->SpawnActor<ABasePlatform>(BasePlatformClass, PlatformLocation, FRotator(0, 0, 0));
	

	IsProtected = false;
}

float AMouseCharacter::GetProtectionTimePercentage()
{
	if(ProtectionTime == 0) return 0;
	return ProtectionTimeLeft / ProtectionTime;
}

bool AMouseCharacter::GetIsJumping()
{
	return GetMovementComponent()->IsFalling();
}

void AMouseCharacter::SpeedUp()
{
	MoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if(MoveComp)
	{
		MoveComp->MaxWalkSpeed += SpeedAddition;
	}
}

int AMouseCharacter::GetScore()
{
	int Score = GetActorLocation().X - ZeroLocation;
	Score *= 0.1;
	return Score;
}

void AMouseCharacter::Death(int NewDeathType)
{
	if(IsProtected && NewDeathType == 0)
	{
		Protection();
		return;
	}

	if (CanDie == false) return;

	AMouseController* MouseController = Cast<AMouseController>(GetController());
	if(MouseController)
	{
		MouseController->Death(GetScore());
	}

	CanDie = false;
	GetWorldTimerManager().SetTimer(CanDieQuickTimerHandle, this, &AMouseCharacter::SetCanDieToTrue, 1);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), FRotator(0, 0, 0));
	DeathType = NewDeathType;
	IsDead = true;

	FinalScore = GetScore(); 

	FVector CameraLocation = Camera->GetComponentLocation();
	Camera->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true));
	Camera->SetWorldLocation(CameraLocation);
}

bool AMouseCharacter::GetIsDead()
{
	return IsDead;
}

int AMouseCharacter::GetFinalScore()
{
	return FinalScore;
}

void AMouseCharacter::PlayStepSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), StepSound, GetActorLocation(), FRotator(0, 0, 0));
}

void AMouseCharacter::EnemyJump()
{
	if(AlreadyEnemyJumped == true) return;

	AlreadyEnemyJumped = true;

	Super::Jump();

	PlayEnemyJumpAnimation();

	
	GetWorldTimerManager().SetTimer(MultiCoinsTimerHandle, this, &AMouseCharacter::AddNewMultiCoin, MultiCoinRate, true, 0);
}

int AMouseCharacter::GetDeathType()
{
	return DeathType;
}

float AMouseCharacter::GetFeetZ()
{
	return FeetPoint->GetComponentLocation().Z;
}

void AMouseCharacter::AddNewMultiCoin()
{
	UE_LOG(LogTemp, Error, TEXT("MultiCoin++!"));
	if(MultiCoinsHeld < 3)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoinSound, GetActorLocation(), FRotator(0, 0, 0));
		MultiCoinsHeld++;
		GameInstance = Cast<UMouseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GameInstance) 
		{
			UE_LOG(LogTemp, Error, TEXT("Adding Multi Coin..."));
			GameInstance->AddCoin();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Game Instance Invalid!"));
		}
	}
	else
	{
		GetWorldTimerManager().PauseTimer(MultiCoinsTimerHandle);
		MultiCoinsHeld = 0;
	}
}

void AMouseCharacter::SetCanDieToTrue()
{
	CanDie = true;
}