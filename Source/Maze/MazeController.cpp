// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeController.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

#include "MazeActor.h"
#include "Engine/World.h"
// Sets default values
AMazeController::AMazeController()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeController::BeginPlay()
{
	
	Super::BeginPlay();
	auto mazeItem = GetWorld()->SpawnActor<AMazeActor>();
	mazeItem->SetActorLocation(FVector(400, 0, 100));
	
}

// Called every frame
void AMazeController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

