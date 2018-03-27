// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileActorEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/SphereComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
// Sets default values
AProjectileActorEnemy::AProjectileActorEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BulletComponent->SetMobility(EComponentMobility::Movable);
	UStaticMesh* EnemyMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	BulletComponent->SetVisibility(true);
	BulletComponent->SetStaticMesh(EnemyMesh);
	BulletComponent->SetSimulatePhysics(true);
	BulletComponent->SetNotifyRigidBodyCollision(true);
	BulletComponent->SetMassOverrideInKg(NAME_None, 10.f);
	BulletComponent->SetEnableGravity(true);
	//BulletComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	BulletComponent->SetMobility(EComponentMobility::Movable);
	auto EnemyMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse"));
	BulletComponent->SetMaterial(0, EnemyMaterial);
	BulletComponent->SetWorldScale3D(FVector(0.2, 0.2, 0.2));

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnPHit");
	OnActorHit.Add(Delegate);
	BulletComponent->OnComponentHit.AddDynamic(this, &AProjectileActorEnemy::OnHit);

	SetRootComponent(BulletComponent);
}

// Called when the game starts or when spawned
void AProjectileActorEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileActorEnemy::Tick(float DeltaTime)
{
	BulletComponent->AddImpulse(ShootDir * 3000);
	Super::Tick(DeltaTime);
}

//void AProjectileActorEnemy::OnPAEHit()
//{
//	print("HIT ME!");
//}

void AProjectileActorEnemy::Initialize(FVector startLocation)
{
	StartLocation = startLocation;
	auto myLoc = GetActorLocation();
	auto diff = startLocation - myLoc;
	//print(startLocation.ToString());
	//print(myLoc.ToString());
	startLocation.Y += 2;
	startLocation.Z -= 17;
	//startLocation.X += 1;
	SetActorLocation(startLocation);
	//print("Init Projectile!");
}

//void AProjectileActorEnemy::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
//{
//	print("HIT ME!");
//}



