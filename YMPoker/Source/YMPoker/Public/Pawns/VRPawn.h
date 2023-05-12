// Copyright Yoav Mashraki 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "VRPawn.generated.h"

class UCameraComponent;
class UMotionControllerComponent;
class AStaticHands;
class UInputMappingContext;
class UInputAction;

UCLASS()
class YMPOKER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void Turn(const FInputActionValue& Value);
	void SetupHands();

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Controller", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMotionControllerComponent> MotionControllerLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Controller", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMotionControllerComponent> MotionControllerRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Hands", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AStaticHands> StaticHandsClass;

	TObjectPtr<AStaticHands> StaticRightHandsRef;
	TObjectPtr<AStaticHands> StaticLeftHandsRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float SnapTurnDegrees;

};
