// Fill out your copyright notice in the Description page of Project Settings.

#include "Shelf.h"
#include "Weapon.h"
#include "Engine/GameEngine.h"

// Sets default values
AShelf::AShelf()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShelf::BeginPlay()
{
	Super::BeginPlay();
	if (!Weapon) 
	{ 
		if (GEngine)
		{
			FString Message = FString::Printf(TEXT("%s has nothing attached"), *(GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
		}
		return; 
	}
}

