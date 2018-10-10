// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!ensure(PhysicsHandle)) { return; }

}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ItemIsPicked) 
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
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
			FVector ItemReleaseLocation = ActorHit->GetActorLocation() + FVector(0, 0, 30);
			FRotator ItemReleaseRotation = ActorHit->GetActorRotation();
			UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
			GrabbedComponent->GetOwner()->SetActorLocation(ItemReleaseLocation);
			GrabbedComponent->GetOwner()->SetActorRotation(ItemReleaseRotation);
			PhysicsHandle->ReleaseComponent();

		}
		else
		{
			PhysicsHandle->ReleaseComponent();
		}
		ItemIsPicked = false;
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
		
		GetWorld()->LineTraceSingleByObjectType(HitResult, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel2), QueryParams);
	}
	else 
	{
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