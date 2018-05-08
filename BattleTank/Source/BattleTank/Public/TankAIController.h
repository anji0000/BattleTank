// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close the AI tank can get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup") 
	float AcceptanceRadius = 8000;

private:
	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossessedTankDeath();
	
};
