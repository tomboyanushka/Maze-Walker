// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGen.h"
#include "MazeActor.h"
#include "MazeController.h"
#include "Engine/World.h"

#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <vector>
#include <list>
using namespace std;

std::vector<std::vector<bool>> maze;

void mazeGenerate()
{
	srand(time(0));

	const int maze_size_x = 80;
	const int maze_size_y = 25;
	list < pair < int, int> > drillers;

	maze.resize(maze_size_y);
	for (size_t y = 0; y<maze_size_y; y++)
		maze[y].resize(maze_size_x);

	for (size_t x = 0; x<maze_size_x; x++)
		for (size_t y = 0; y<maze_size_y; y++)
			maze[y][x] = false;

	drillers.push_back(make_pair(maze_size_x / 2, maze_size_y / 2));
	while (drillers.size()>0)
	{
		list < pair < int, int> >::iterator m, _m, temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m != _m)
		{
			bool remove_driller = false;
			switch (rand() % 4)
			{
			case 0:
				(*m).second -= 2;
				if ((*m).second<0 || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second + 1][(*m).first] = true;
				break;
			case 1:
				(*m).second += 2;
				if ((*m).second >= maze_size_y || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second - 1][(*m).first] = true;
				break;
			case 2:
				(*m).first -= 2;
				if ((*m).first<0 || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second][(*m).first + 1] = true;
				break;
			case 3:
				(*m).first += 2;
				if ((*m).first >= maze_size_x || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second][(*m).first - 1] = true;
				break;
			}
			if (remove_driller)
				m = drillers.erase(m);
			else
			{
				drillers.push_back(make_pair((*m).first, (*m).second));
				// uncomment the line below to make the maze easier 
				// if (rand()%2) 
				drillers.push_back(make_pair((*m).first, (*m).second));

				maze[(*m).second][(*m).first] = true;
				++m;
			}
		}
	}
}

// Sets default values
AMazeGen::AMazeGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeGen::BeginPlay()
{
	Super::BeginPlay();
	mazeGenerate();

	for (size_t y = 0; y<maze_size_y; y++)
		for (size_t x = 0; x<maze_size_x; x++)
		{
			if (maze[y][x] == true)
			{
				auto mazeItem = GetWorld()->SpawnActor<AMazeActor>();
				mazeItem->SetActorLocation(FVector(400* y, 400*x, 0));
			}
				//printf(".");
			else
				printf("#");
		}

	
}

// Called every frame
void AMazeGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


