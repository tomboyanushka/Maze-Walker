// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

#include "MyTriggerBox.h"
#include "Engine/World.h"
#include "FP_FirstPerson/FP_FirstPersonHUD.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Public/CanvasTypes.h"
#include "Runtime/Core/Public/Internationalization/Text.h"
#include "Runtime/Engine/Public/CanvasItem.h"


#define printf(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

FText GameOverText = FText::FromString("GAME OVER!");
AMyTriggerBox::AMyTriggerBox()
{
	
	
	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

// Called when the game starts or when spawned
void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

void AMyTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	auto hud = Cast<AFP_FirstPersonHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	hud->isGameOver = true;
	if (OtherActor && (OtherActor != this)) {
		// print to screen using above defined method when actor enters trigger box
		print("Overlap Begin");
		//printFString("Other Actor = %s", *OtherActor->GetName());

		
	}
}

void AMyTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		// print to screen using above defined method when actor leaves trigger box
		print("Overlap End");
		//printFString("%s has left the Trigger Box", *OtherActor->GetName());
	}
}

