// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class AWeapon;
class AShelf;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DKRSTORE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();
	bool IsItemPicked();
	void SetReach(float Reach);

	/** Used in Character Blueprint to get the actor of the picked object. */
	AActor* GetPickedActor();
	AShelf* GetShelf() { return Shelf; }
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	FVector DropOffset = FVector(0,0,0);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float Reach = 200;

	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	const FHitResult GetObjectInReach();

	FVector GetReachLineStart();
	FVector GetReachLineEnd();
	FVector GetLineEndForInspect();
	bool ItemIsPicked = false;

	AShelf* Shelf = nullptr;
	AWeapon* Weapon = nullptr;
};
