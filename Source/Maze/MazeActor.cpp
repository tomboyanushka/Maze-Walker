// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "FP_FirstPerson/FP_FirstPersonHUD.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

// Sets default values
AMazeActor::AMazeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetMobility(EComponentMobility::Movable);
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	MeshComponent->SetVisibility(true);
	MeshComponent->SetStaticMesh(Mesh);


	MeshComponent->SetMobility(EComponentMobility::Movable);
	auto mat = LoadObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Brick_Clay_Old"));
	MeshComponent->SetMaterial(0, mat);
	MeshComponent->SetWorldScale3D(FVector(4, 4, 4));
	SetRootComponent(MeshComponent);

	

}

// Called when the game starts or when spawned
void AMazeActor::BeginPlay()
{
	Super::BeginPlay();
	 
}

// Called every frame
void AMazeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

