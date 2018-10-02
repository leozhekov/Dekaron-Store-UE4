// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DkrStoreCharacter.h"
#include "DkrStoreProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "Grabber.h"
#include "HUDControlComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ADkrStoreCharacter

ADkrStoreCharacter::ADkrStoreCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera

}

void ADkrStoreCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Grabber = FindComponentByClass<UGrabber>();
	HUDControl = FindComponentByClass<UHUDControlComponent>();
	if (!ensure(Grabber) || !ensure(HUDControl)) { return; }
	Grabber->SetReach(Reach);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADkrStoreCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind object events
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &ADkrStoreCharacter::Grab);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &ADkrStoreCharacter::Drop);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADkrStoreCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADkrStoreCharacter::MoveRight);


}
void ADkrStoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckForItemPicked())
	{
		if (CheckForShelf())
		{
			HUDControl->ShelfInRange();
		}
		else
		{
			HUDControl->HasItem();
		}
	}
	else
	{
		if (CheckIfItemWithinRange())
		{
			HUDControl->ItemInRange();
		}
		else
		{
			HUDControl->RemoveAll();
		}
	}

}

//Used in blueprint to check for a picked actor when inspecting
AActor* ADkrStoreCharacter::PickedActor()
{
	if (Grabber->IsItemPicked())
	{
		return Grabber->GetPickedActor();
	}
	else 
	{
		return nullptr;
	}
}

bool ADkrStoreCharacter::CheckForItemPicked()
{
	return Grabber->IsItemPicked();
}

// if CheckForItemPicked returns false call this every tick to check if there's a pick up item in range
bool ADkrStoreCharacter::CheckIfItemWithinRange()
{
	FHitResult HitResult = LineTraceByChannel(1);
	if (HitResult.GetActor())
	{
		return true;
	}
	else
	{
		return false;
	}
}


// if CheckForItemPicked returns true call this every tick to check if close to a shelf
bool ADkrStoreCharacter::CheckForShelf()
{
	FHitResult HitResult = LineTraceByChannel(2);
	
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// Helper method for linetracing
FHitResult ADkrStoreCharacter::LineTraceByChannel(int Channel)
{
	FVector StartLocation;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(StartLocation, Rotation);

	FVector EndLocation = StartLocation + (Rotation.Vector() * Reach);
	FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;
	switch (Channel)
	{
	case 1:
		GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1), QueryParams);
		break;
	case 2:
		GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel2), QueryParams);
		break;
	}
	

	return HitResult;
}



void ADkrStoreCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADkrStoreCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void ADkrStoreCharacter::Grab()
{
	if (!Grabber->IsItemPicked()) 
	{
		Grabber->Grab();
	}
}

void ADkrStoreCharacter::Drop()
{
	if (Grabber->IsItemPicked())
	{
		Grabber->Release();
	}
}

