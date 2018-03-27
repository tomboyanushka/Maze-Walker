// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeController.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "MazeActor.h"
#include "Engine/World.h"
#include "FP_FirstPerson/FP_FirstPersonHUD.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"

// Sets default values
AMazeController::AMazeController()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeController::BeginPlay()
{
	
}

// Called every frame
void AMazeController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

