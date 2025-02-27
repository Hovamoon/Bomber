﻿// Copyright (c) Yevhenii Selivanov

#pragma once

#include "Components/ActorComponent.h"
//---
#include "FootTrailsTypes.h"
#include "Structures/Cell.h"
//---
#include "FootTrailsGeneratorComponent.generated.h"

class UFootTrailsDataAsset;
class UStaticMesh;

/**
 * Is main logic component that generates foot trails.
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOOTTRAILSGENERATORRUNTIME_API UFootTrailsGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties. */
	UFootTrailsGeneratorComponent();

	/** Returns the data asset that contains all the assets and tweaks of Foot Trails game feature.
	 * @see UFootTrailsGeneratorComponent::FootTrailsDataTableInternal */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "C++")
	FORCEINLINE UFootTrailsDataAsset* GetFootTrailsDataAsset() const { return FootTrailsDataAssetInternal; }

	/** Returns the random foot trail instance for given types. */
	UFUNCTION(BlueprintPure, Category = "C++")
	const UStaticMesh* GetRandomMesh(EFootTrailType FootTrailType) const;

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Called when the game ends. */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Loads all foot trails archetypes. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected))
	void Init();

	/** Spawns given Foot Trail by its type on the specified cell. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected))
	void SpawnFootTrail(EFootTrailType FootTrailType, const FCell& Cell, float CellRotation);

	/** Contains all the assets and tweaks of Foot Trails game feature. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "C++", meta = (BlueprintProtected, DisplayName = "Foot Trails Data Asset"))
	TObjectPtr<UFootTrailsDataAsset> FootTrailsDataAssetInternal = nullptr;

	/** Converts actors with static meshes to instanced static meshes. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Transient, Category = "C++", meta = (BlueprintProtected, DisplayName = "Instanced Static Mesh Actor"))
	TObjectPtr<class AInstancedStaticMeshActor> InstancedStaticMeshActorInternal = nullptr;

	/** Loaded foot trails archetypes for all levels. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Transient, Category = "C++", meta = (BlueprintProtected, DisplayName = "Foot Trail Instances"))
	TMap<FFootTrailArchetype, TObjectPtr<UStaticMesh>> FootTrailInstancesInternal;
};
