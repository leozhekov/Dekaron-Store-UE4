// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUDControlComponent.generated.h"

class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DKRSTORE_API UHUDControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHUDControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Hides all widgets
	void RemoveAll();

	//Shows drop and inspect widget
	void HasItem();

	//Shows only leave to shelf widget
	void ShelfInRange();

	//shows only pickup widget
	void ItemInRange();


private:

	void Remove(UUserWidget*  Widget);
	void Add(UUserWidget*  Widget);
	void AddAllToViewport();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UUserWidget> PickUpKeyWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UUserWidget> DropKeyWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UUserWidget> InspectKeyWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UUserWidget> LeaveOnShelfKeyWidget;

	UUserWidget* PickUpWidget;
	UUserWidget* DropWidget;
	UUserWidget* InspectWidget;
	UUserWidget* LeaveOnShelfWidget;
	bool AlreadyRemoved;
};
