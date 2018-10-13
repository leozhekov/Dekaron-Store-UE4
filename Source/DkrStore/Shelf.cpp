// Fill out your copyright notice in the Description page of Project Settings.

#include "Shelf.h"
#include "Weapon.h"

// Sets default values
AShelf::AShelf()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShelf::BeginPlay()
{
	Super::BeginPlay();
	if (!Weapon) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Testing %s has nothing attatched"), *(GetName()))
		return; 
	}
	UE_LOG(LogTemp, Warning, TEXT("Testing %s has attached %s"), *(GetName()), *(Weapon->GetName()))
}

// Called every frame
void AShelf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

