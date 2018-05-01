// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "BattleTank.h"



void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

// Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // OUT parameter
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location if ray trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "de-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// ray-trace along that look direction, and see what we hit (up to a max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}