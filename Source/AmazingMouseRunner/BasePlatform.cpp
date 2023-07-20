// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MouseCharacter.h"
#include "RunGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePlatform::ABasePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	SpawnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnTrigger"));
	SpawnTrigger->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DestroyTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyTrigger"));
	DestroyTrigger->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DeathTrigger"));
	DeathTrigger->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();

	SpawnTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABasePlatform::SpawnOverlap);
	DestroyTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABasePlatform::DestroyOverlap);
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABasePlatform::DeathOverlap);
}

void ABasePlatform::SetPlatformClass()
{
	if (NextPlatformNotRandom == false)
	{
		ARunGameMode* GameMode = Cast<ARunGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode != nullptr)
		{
			TArray<TSubclassOf<ABasePlatform>> PlatformTypes = GameMode->GetPlatformTypes();

			if(PlatformTypes.Num()>0)
			{
				int random = (rand() % PlatformTypes.Num());

				PlatformClass = PlatformTypes[random];
			}
		}
	}
}

void ABasePlatform::SpawnOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	SetPlatformClass();

	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse != nullptr && Triggered == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Platform..."));

		FVector Location = SpawnPoint->GetComponentLocation();
		FRotator Rotation = GetActorRotation();

		GetWorld()->SpawnActor<ABasePlatform>(PlatformClass, Location, Rotation);

		Mouse->SpeedUp();

		Triggered = true;
	} 
}

void ABasePlatform::DestroyOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse != nullptr)
	{
		DestroyPlatformAndElements();
	} 
}

void ABasePlatform::DeathOverlap(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dying..."));
		Mouse->Death(1);
	} 
}

TArray<TSubclassOf<AActor>> ABasePlatform::GetElementsClasses()
{
	 return ElementsClasses;
}

void ABasePlatform::AddElement(AActor* Element)
{
	ChildElements.Add(Element);
}

UMaterial* ABasePlatform::GetPlatformMaterialByIndex(int Index)
{
	switch(Index)
	{
		case 0:
			return Materials[0];
			break;
		case 1:
			return Materials[1];
			break;
		case 2:
			return Materials[2];
			break;
		default:
			return Materials[0];
			break;
	}
}

void ABasePlatform::DestroyElements()
{
	int Num = ChildElements.Num();
	if(Num > 0)
	{
		for (int i = 0; i <= Num; i++)
		{
			ChildElements.Top()->Destroy();
		}
	}
}

void ABasePlatform::DestroyPlatformAndElements()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroying Platform..."));
	DestroyElements();
	Destroy();
}