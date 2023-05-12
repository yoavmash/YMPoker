// Copyright Yoav Mashraki 2023


#include "Pawns/StaticHands.h"

AStaticHands::AStaticHands()
{
	PrimaryActorTick.bCanEverTick = true;

	HandRoot = CreateDefaultSubobject<USceneComponent>(TEXT("HandRoot"));
	RootComponent = HandRoot;

	HandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(HandRoot);
}

void AStaticHands::BeginPlay()
{
	Super::BeginPlay();

}

void AStaticHands::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaticHands::SetupMesh(bool bIsRightHand)
{
	if (bIsRightHand)
	{
		if (HandRightMesh) {
			HandMesh->SetStaticMesh(HandRightMesh);
		}
	}
	else
	{
		if (HandLeftMesh)
		{
			HandMesh->SetStaticMesh(HandLeftMesh);
		}
	}
}

