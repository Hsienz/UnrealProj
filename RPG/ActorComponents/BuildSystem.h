// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMCActorComponent.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "BuildSystem.generated.h"

class USocketComponent;
class ABuildingPart;
class UBuildingPartPrimaryDataAsset;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UInputAction;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBuildSystem : public UIMCActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess=true))
	UInputAction* ToggleBuildModeInputAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess=true))
	UInputAction* BuildInputAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess))
	UInputAction* RotateBuildPreviewInputAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Input",meta=(AllowPrivateAccess))
	UInputAction* SwitchHoldingBuildingPartPrimaryDataAssetInputAction;
	
	
public:	
	// Sets default values for this component's properties
	UBuildSystem();

	void ToggleBuildMode(const FInputActionValue& Value);

	void Build(const FInputActionValue& Value);

	bool BuildMode;
	
	bool bBuildLocationHit;
	TArray<FHitResult> HitResults;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BuildSetting )
	float BuildReachDistance = 500;

	// UPROPERTY(EditAnywhere)
	// TSubclassOf<ABuildingPart> BuildingPartBlueprint;

	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UStaticMeshComponent> BuildPreview;

	FTimerHandle RotatePreviewTimerHandle;
	void RotateBuildPreview();
	void StopRotationBuildOPreview();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Build)
	TArray<UBuildingPartPrimaryDataAsset*> HoldingBuildingPartPrimaryDataAssets;
	int32 CurrentHoldingBuildingPartPrimaryDataAssetIndex;
	UBuildingPartPrimaryDataAsset* GetCurrentHoldingBuildingPartPrimaryDataAsset() const;
	void SwitchHoldingBuildingPartPrimaryDataAsset( const FInputActionValue& Value);

	void AttemptUpdateBuildPreview();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	USocketComponent* GetSnappableSocketComponent();

	void AttemptCreateBuildPreview();

	void AttemptDestroyBuildPreview();
	
	void UpdateHitResults();
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent) override;
		
};

