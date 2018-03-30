// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FP_FirstPersonHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "Runtime/Engine/Public/CanvasTypes.h"
#include "FP_FirstPersonCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <string>

AFP_FirstPersonHUD::AFP_FirstPersonHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("/Game/Roboto-Light_Font.Roboto-Light_Font"));
	if (FontObject.Object)
	{
		Font = FontObject.Object;
	}
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

/** This method draws a very simple crosshair */
void AFP_FirstPersonHUD::DrawHUD()
{
	Super::DrawHUD();

	// Find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// Offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
										   (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)) );
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (showTopDownView)
	{
		FVector2D ScreenLocation;
		
		PlayerController->ProjectWorldLocationToScreen(playerLocation, ScreenLocation);
		CrosshairDrawPosition = ScreenLocation;
	}
	
	// Draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	FText GameOverText = FText::FromString("GAME OVER! Press Enter to Replay");
	auto FPPlayer = (AFP_FirstPersonCharacter*)(PlayerController);
	FText HealthTextString = FText::FromString((std::string("Health: ") + std::to_string(Health)).c_str());
	FLinearColor TheFontColour = FLinearColor(1.0f, 1.0f, 1.0f);
	auto pos = FVector2D(Center.X - 200, Center.Y);
	auto HealthPos = FVector2D(20, 20);
	
	FCanvasTextItem NewText(pos, GameOverText, Font, TheFontColour);
	FCanvasTextItem HealthText(HealthPos, HealthTextString, Font, TheFontColour);

	//Text Scale
	NewText.Scale.Set(2, 2);
	
	
	Canvas->DrawItem(HealthText);
	Canvas->DrawItem( TileItem );
	
	if (isGameOver == true)
	{
		//Draw
		Canvas->DrawItem(NewText);
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Enter))
		{
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}
		
	}
	if (Health <= 0)
	{
		//Draw
		Canvas->DrawItem(NewText);
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Enter))
		{
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}

	}

}
