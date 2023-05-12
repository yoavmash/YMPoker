// Copyright Yoav Mashraki 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticHands.generated.h"

UCLASS()
class YMPOKER_API AStaticHands : public AActor
{
	GENERATED_BODY()
	
public:	
	AStaticHands();
	virtual void Tick(float DeltaTime) override;

	void SetupMesh(bool bIsRightHand);

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> HandRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh> HandLeftMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hand", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh> HandRightMesh;
};
