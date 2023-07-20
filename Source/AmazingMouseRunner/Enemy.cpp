// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "MouseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);

	DeathBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DeathBox"));
	DeathBox->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	USkeletalMeshComponent* EnemyMesh = GetMesh();

	if (EnemyMesh != nullptr)
	{
		EnemyMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true));
		EnemyMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	}

	Cap = GetCapsuleComponent();
	if(Cap != nullptr)
	{
		Cap->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Cap->OnComponentHit.AddDynamic(this, &AEnemy::OnMeshHit);
	DeathBox->OnComponentHit.AddDynamic(this, &AEnemy::OnBoxHit);
}

void AEnemy::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::OnMeshHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse == nullptr) return;

	Mouse->Death(0);
}

void AEnemy::OnBoxHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMouseCharacter* Mouse = Cast<AMouseCharacter>(OtherActor);

	if(Mouse == nullptr) return;

	if(Mouse->GetIsDead() == true || Mouse->GetFeetZ() < DeathBox->GetComponentLocation().Z) return;

	Mouse->EnemyJump();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), FRotator(0, 0, 0));

	IsDead = true;
}

bool AEnemy::GetIsDead()
{
	return IsDead;
}

