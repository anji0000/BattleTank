// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Tank.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}

// Tick
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank)) {
		// TODO move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
		
		// aim at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// fire if ready
		ControlledTank->Fire(); // TODO limit firing rate
	}
}




