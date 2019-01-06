// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DkrStoreCharacter.generated.h"

class UInputComponent;
class AShelf;

UCLASS(config=Game)
class ADkrStoreCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ADkrStoreCharacter();

protected:

	virtual void BeginPlay();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	
	/** Used in blueprint to check for a picked actor when inspecting */
	UFUNCTION(BlueprintCallable, Category = "Inspection")
	AActor* PickedActor();

	/** Used in blueprint to set the flag when item is being inspected */
	UFUNCTION(BlueprintCallable, Category = "Inspection")
	void SetItemIsBeingInspected(bool IsItemBeingInspected) { ItemIsBeingInspected = IsItemBeingInspected; };

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool CheckForItemPicked();

	/** if CheckForItemPicked returns true call this every tick to check if close to a shelf */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool CheckForShelf();

	/** if CheckForItemPicked returns false call this every tick to check if there's a pick up item in range */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool CheckIfItemWithinRange();

	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Reach = 300;

	class UGrabber* Grabber = nullptr;
	void Grab();
	void Drop();

	/** Helper method for linetracing */
	FHitResult LineTraceByChannel(int Channel);
	bool ItemIsBeingInspected;

	class UHUDControlComponent* HUDControl = nullptr;
};

