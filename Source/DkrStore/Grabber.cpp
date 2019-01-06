// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Weapon.h"
#include "Shelf.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Physics handle missing"))
		return; 
	}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ItemIsPicked) 
	{
		PhysicsHandle->SetTargetLocation(GetLineEndForInspect());
		FRotator TargetRotation = PhysicsHandle->GetGrabbedComponent()->GetOwner()->GetActorRotation();
		PhysicsHandle->SetTargetRotation(TargetRotation);
	}
}

void UGrabber::Grab() 
{
	FHitResult HitResult = GetObjectInReach();
	AActor* ActorHit = HitResult.GetActor();
	UPrimitiveComponent* Component = GetObjectInReach().GetComponent();
	if (ActorHit) 
	{
		PhysicsHandle->GrabComponent(Component, NAME_None, Component->GetOwner()->GetActorLocation(), true);
		ItemIsPicked = true;
		Weapon = (AWeapon*)Component->GetOwner();
		Shelf = Weapon->GetShelf();
	}
}

void UGrabber::Release() 
{
	if (ItemIsPicked)
	{ 
		FHitResult HitResult = GetObjectInReach();
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit)
		{	
			AShelf* ShelfHit = (AShelf*) ActorHit;
			if (ShelfHit->GetName() == Shelf->GetName())
			{
				FVector ItemReleaseLocation = Weapon->GetStartupLocation() + DropOffset;
				FRotator ItemReleaseRotation = Weapon->GetStartupRotation();
				UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
				GrabbedComponent->GetOwner()->SetActorLocation(ItemReleaseLocation);
				GrabbedComponent->GetOwner()->SetActorRotation(ItemReleaseRotation);
				PhysicsHandle->ReleaseComponent();
				ItemIsPicked = false;
			}
		}
		else
		{
			PhysicsHandle->ReleaseComponent();
			ItemIsPicked = false;
		}
	}
}

bool UGrabber::IsItemPicked()
{
	return ItemIsPicked;
}

void UGrabber::SetReach(float ReachToSet)
{
	Reach = ReachToSet;
}

const FHitResult UGrabber::GetObjectInReach()
{
	FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;
	if (ItemIsPicked)
	{
		// Line-tracing for a shelf object - Collision preset "Shelf"
		GetWorld()->LineTraceSingleByObjectType(HitResult, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel2), QueryParams);
	}
	else 
	{
		//Line-tracing for a pickup object - Collision preset "Pick Up"
		GetWorld()->LineTraceSingleByObjectType(HitResult, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1), QueryParams);
	}

	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	return Location;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	return Location + (Rotation.Vector() * Reach);
}

AActor* UGrabber::GetPickedActor()
{
	return PhysicsHandle->GetGrabbedComponent()->GetOwner();
}

FVector UGrabber::GetLineEndForInspect()
{
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	return Location + (Rotation.Vector() * (Reach * 0.7));
}
