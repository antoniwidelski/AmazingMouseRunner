// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "MouseCharacter.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &AObstacle::OnHit);
}

void AObstacle::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse == nullptr) return;

	Mouse->Death(0);
}