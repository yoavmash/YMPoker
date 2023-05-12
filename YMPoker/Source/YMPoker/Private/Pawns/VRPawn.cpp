// Copyright Yoav Mashraki 2023


#include "Pawns/VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Pawns/StaticHands.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayFunctionLibrary.h"

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

	SnapTurnDegrees = 30.f;
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		SetupHands();
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);
		if (TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Controller))
		{
			if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AVRPawn::Turn(const FInputActionValue& Value)
{
	float YawDelta = Value.Get<float>() > 0.f ? SnapTurnDegrees : SnapTurnDegrees * -1.f;

	FVector CameraWorldLocation = Camera->GetComponentLocation();
	FTransform CameraRelativeTransform = Camera->GetRelativeTransform();
	FRotator CombineRootRotator = GetActorRotation();
	CombineRootRotator.Yaw += YawDelta;
	FTransform NewTransform = FTransform(CombineRootRotator, GetActorLocation());

	AddActorWorldRotation(FRotator(0.f, YawDelta, 0.f));

	FTransform CombineTransform = CameraRelativeTransform * NewTransform;
	FVector NewLocation = CameraWorldLocation - CombineTransform.GetLocation() + GetActorLocation();

	FHitResult HitResult;
	SetActorLocation(NewLocation, false, &HitResult, ETeleportType::TeleportPhysics);
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

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &AVRPawn::Turn);
	}
}

