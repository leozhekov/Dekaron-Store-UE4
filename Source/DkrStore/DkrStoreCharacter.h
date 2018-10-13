// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DkrStoreCharacter.generated.h"

class UInputComponent;
class Shelf;
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
	
	UFUNCTION(BlueprintCallable, Category = "Inspection")
	AActor* PickedActor();

	UFUNCTION(BlueprintCallable, Category = "Inspection")
	void SetItemIsBeing
	
	(bool IsItemBeingInspected) { ItemIsBeingInspected = IsItemBeingInspected; };

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool CheckForItemPicked();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool CheckForShelf();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	bool CheckIfItemWithinRange();

	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Reach = 300;

	class UGrabber* Grabber = nullptr;

	void Grab();
	void Drop();

	FHitResult LineTraceByChannel(int Channel);
	bool ItemIsBeingInspected;

	class UHUDControlComponent* HUDControl = nullptr;
};

