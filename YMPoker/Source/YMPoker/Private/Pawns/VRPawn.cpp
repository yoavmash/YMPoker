// Copyright Yoav Mashraki 2023


#include "Pawns/VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Pawns/StaticHands.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SceneRoot);

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	MotionControllerLeft->SetupAttachment(SceneRoot);
	MotionControllerLeft->SetTrackingSource(EControllerHand::Left);

	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));
	MotionControllerRight->SetupAttachment(SceneRoot);
	MotionControllerRight->SetTrackingSource(EControllerHand::Right);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHands();
}

void AVRPawn::SetupHands()
{
	if (StaticHandsClass)
	{
		StaticRightHandsRef = GetWorld()->SpawnActor<AStaticHands>(StaticHandsClass, FVector::ZeroVector, FRotator::ZeroRotator);
		StaticRightHandsRef->SetupMesh(true);
		StaticRightHandsRef->AttachToComponent(MotionControllerRight, FAttachmentTransformRules::SnapToTargetIncludingScale);

		StaticLeftHandsRef = GetWorld()->SpawnActor<AStaticHands>(StaticHandsClass, FVector::ZeroVector, FRotator::ZeroRotator);
		StaticLeftHandsRef->SetupMesh(false);
		StaticLeftHandsRef->AttachToComponent(MotionControllerLeft, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

