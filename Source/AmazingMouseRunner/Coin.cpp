// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/StaticMeshComponent.h"
#include "MouseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MouseGameInstance.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::Overlapped);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Spin(DeltaTime);
}

void ACoin::Overlapped(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse != nullptr && CanCollect == true)
	{
		UMouseGameInstance* GameInstance = Cast<UMouseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstance == nullptr) return;

		CanCollect = false;
		UE_LOG(LogTemp, Warning, TEXT("Mouse Overlapped..."));
		GameInstance->AddCoin();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoinSound, GetActorLocation(), FRotator(0, 0, 0));
		Destroy();
	}
}

void ACoin::Spin(float DeltaTime)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += SpinSpeed * DeltaTime;

	SetActorRotation(NewRotation);
}