// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DkrStoreGameMode.h"
#include "DkrStoreHUD.h"
#include "DkrStoreCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADkrStoreGameMode::ADkrStoreGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/BP_DkrStoreCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADkrStoreHUD::StaticClass();
}
