// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Shelf.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Testing %s is not attached to anything"), *(GetName()))
		return; 
	}
	UE_LOG(LogTemp, Warning, TEXT("Testing %s is attached to %s"), *(GetName()), *(Shelf->GetName()))

	StartupLocation = GetActorLocation();
	StartupRotation = GetActorRotation();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

