// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMaze.h"

#include "MazeGen.h"
#include "MazeActor.h"
#include "MazeController.h"
#include "Engine/World.h"
#include "MyTriggerBox.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
using namespace std;
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
int **l;
int width = 34; 
int height = 15;
int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };
int dx1[4] = { 0, 2, 0, -2 }, dy1[4] = { 2, 0, -2, 0 };

//int entry;
///int exit/

int myrand(int i) { return rand() % i; };


void back(int x, int y)
{

	static int v[4] = { 0, 1, 2, 3 };
	random_shuffle(&v[0], &v[4], myrand);

	for (int i = 0; i < 4; i++)
	{
		int k = v[i];
		int x1 = x + dx[k], y1 = y + dy[k];
		x += dx1[k];
		y += dy1[k];
		if (y < height - 1 && x < width - 1 &&
			y  > 0 && x  > 0)
		{
			if (l[x1][y1] == 1 && l[x][y] == 1)
			{
				l[x1][y1] = l[x][y] = 0;
				back(x, y);
			}
		}
		x -= dx1[k];
		y -= dy1[k];
	}
}
// Sets default values
AProceduralMaze::AProceduralMaze()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	 
	//auto a = CreateDefaultSubobject<ACharacter>("/Game/BP_Enemy.BP_Enemy");
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnBPClass(TEXT("/Game/BP_Enemy"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		EnemyActorClass = PlayerPawnBPClass.Class;
	}

}

// Called when the game starts or when spawned
void AProceduralMaze::BeginPlay()
{
	Super::BeginPlay();
		srand(time(NULL));
		l = new int*[width];
		for (int i = 0; i < width; i++)
		{
			l[i] = new int[height];
			for (int j = 0; j < height; j++)
				l[i][j] = 1;
		}
		back(1, 1);
		l[1][1] = 0;
		l[0][1] = 0;
		l[33][13] = 0;
	
		for (int i = 0; i < 14; ++i)
		{
			l[33][i] = 0;
		}
		for (int i = 0; i < 14; ++i)
		{
			if (l[5][i] == 0)
			{

				auto v = FVector(400 * i - 100, 400 * 5 + 100, 90);
				auto r = FRotator(0, 90, 0);
				//auto EnemyLoc = GetWorld()->SpawnActor<ACharacter>(EnemyActorClass, v, r);
				//if (EnemyLoc != nullptr)
				{
					//EnemyLoc->SetActorLocation(FVector(400 * 1 - 100, 400 * 0 + 100, 90));
				}
			}
			if (l[15][i] == 0)
			{
				auto v = FVector(400 * i - 100, 400 * 15 + 100, 90);
				auto r = FRotator(0, 90, 0);
				//auto EnemyLoc = GetWorld()->SpawnActor<ACharacter>(EnemyActorClass, v, r);
			}
			if (l[31][i] == 0)
			{
				auto v = FVector(400 * i - 100, 400 * 31 + 100, 90);
				auto r = FRotator(0,90,0);
				//auto EnemyLoc = GetWorld()->SpawnActor<ACharacter>(EnemyActorClass, v, r);
			}

		}
			

		int endI;
		for (int i = 0; i < 14; ++i)
		{
			if (l[31][i] == 0) {
				l[32][i] = 0;
				endI = i;
				break;
			}
		}
		auto endTrigger = GetWorld()->SpawnActor<AMyTriggerBox>();
		endTrigger->SetActorLocation(FVector(400 * endI, 400 * 33, 0));
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (l[i][j] == 1)
				{
					auto mazeItem = GetWorld()->SpawnActor<AMazeActor>();
					mazeItem->SetActorLocation(FVector(400 * j, 400 * i, 0));
				}
					//cout << "#";
				else
					cout << ",";
			}
			//cout << endl;
		}
}

// Called every frame
void AProceduralMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}