// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shelf.generated.h"


UCLASS()
class DKRSTORE_API AShelf : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class AWeapon * Weapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AWeapon* GetWeapon()
	{
		return Weapon;
	}
	
};
