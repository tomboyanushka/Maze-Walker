// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGen.generated.h"


UCLASS()
class MAZE_API AMazeGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	const int maze_size_x = 80;
	const int maze_size_y = 25;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	
};
