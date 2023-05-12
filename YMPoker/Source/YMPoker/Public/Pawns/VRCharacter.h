// Copyright Yoav Mashraki 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class YMPOKER_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void BeginTeleport();

private:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> VRRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> DestinationMarker;

	void UpdateDestinationMarker();

	UPROPERTY(EditAnywhere)
	float MaxTeleportDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TeleportAction;

	void FinishTeleport();
	void StartFade(float FromAlpha, float ToAlpha);

	UPROPERTY(EditAnywhere)
	float TeleportFadeTime;

	bool FindTeleportDestination(FVector& OutLocation);

	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtent;
};
