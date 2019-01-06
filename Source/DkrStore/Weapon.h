// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class DKRSTORE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shelf")
	class AShelf * Shelf;

public:
	FVector GetStartupLocation() { return StartupLocation; }
	FRotator GetStartupRotation() { return StartupRotation; }

	AShelf* GetShelf() { return Shelf; }
	
private:
	FVector StartupLocation;
	FRotator StartupRotation;
	
};
