// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Shelf.h"
#include "Engine/GameEngine.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (!Shelf) 
	{
		if (GEngine)
		{
			FString Message = FString::Printf(TEXT("%s is not attached to anything"), *(GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Message);
		}
		return; 
	} 


	StartupLocation = GetActorLocation();
	StartupRotation = GetActorRotation();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

