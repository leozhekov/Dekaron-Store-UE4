// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDControlComponent.h"
#include "UMG/Public/Blueprint/UserWidget.h"


// Sets default values for this component's properties
UHUDControlComponent::UHUDControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHUDControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!ensure(PickUpKeyWidget) || !ensure(DropKeyWidget) || !ensure(InspectKeyWidget) || !ensure(LeaveOnShelfKeyWidget)) { return; }
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PickUpWidget = CreateWidget(PlayerController, PickUpKeyWidget);
	DropWidget = CreateWidget(PlayerController, DropKeyWidget);
	InspectWidget = CreateWidget(PlayerController, InspectKeyWidget);
	LeaveOnShelfWidget = CreateWidget(PlayerController, LeaveOnShelfKeyWidget);
	AddAllToViewport();
	RemoveAll();
}




// Called every frame
void UHUDControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UHUDControlComponent::RemoveAll()
{
	Remove(PickUpWidget);
	Remove(DropWidget);
	Remove(InspectWidget);
	Remove(LeaveOnShelfWidget);
}



void UHUDControlComponent::HasItem()
{
	RemoveAll();
	Add(DropWidget);
	Add(InspectWidget);
}

void UHUDControlComponent::ShelfInRange()
{
	RemoveAll();
	Add(LeaveOnShelfWidget);
}

void UHUDControlComponent::ItemInRange()
{
	RemoveAll();
	Add(PickUpWidget);
}



void UHUDControlComponent::AddAllToViewport()
{
	PickUpWidget->AddToViewport();
	DropWidget->AddToViewport();
	InspectWidget->AddToViewport();
	LeaveOnShelfWidget->AddToViewport();
}


void UHUDControlComponent::Remove(UUserWidget* Widget)
{
	if (Widget->Visibility != ESlateVisibility::Hidden)
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHUDControlComponent::Add(UUserWidget* Widget)
{
	if (Widget->Visibility != ESlateVisibility::Visible)
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}
