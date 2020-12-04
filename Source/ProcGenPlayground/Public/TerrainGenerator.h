// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <libnoise.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainGenerator.generated.h"

UENUM(BlueprintType)
namespace qualities {
	enum PerlinNoiseQuality {
		QUALITY_FAST UMETA(DisplayName = "Fast Quality"),
		QUALITY_STD UMETA(DisplayName = "Standard Quality"),
		QUALITY_BEST UMETA(DisplayName = "Best Quality"),
	};
}

UCLASS()
class PROCGENPLAYGROUND_API ATerrainGenerator : public AActor
{
	GENERATED_BODY()

		
	
public:	
	// Sets default values for this actor's properties
	ATerrainGenerator();

	//Returns a value from the noise
	UFUNCTION(BlueprintCallable, meta = (Keywords = "noise perlin"), Category = "Perlin")
	float GetValue(float x, float y, float z) const;

	//The main function to call to get noise output
	UFUNCTION(BlueprintCallable, Category = "Perlin")
		void SetupOptions(
			float Frequency,
			float Lacunarity,
			qualities::PerlinNoiseQuality NoiseQuality,
			int OctaveCount,
			float Persistence,
			int Seed
		);
	//GETTER LIST
	UFUNCTION(BlueprintCallable, Category = "Perlin")
	float GetFrequency() const;

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	float GetLacunarity() const;

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	qualities::PerlinNoiseQuality GetNoiseQuality() const;

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	int GetOctaveCount() const;

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	float GetPersistence() const;

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	int GetSeed() const;

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	int GetSourceModuleCount() const;

	//SETTER LIST

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetFrequency(float frequency);

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetLacunarity(float lacunarity);

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetNoiseQuality(qualities::PerlinNoiseQuality noiseQuality);

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetOctaveCount(int octaveCount);

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetPersistence(float persistence);

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetSeed(int seed);

	UFUNCTION(BlueprintCallable, Category = "Perlin")
	void SetRandomSeed();

private:
	//The core Perlin Noise object
	noise::module::Perlin perlinNoise;

	//Convertion methods for noise data
	noise::NoiseQuality convertBPNoiseQuality(qualities::PerlinNoiseQuality quality) const;
	qualities::PerlinNoiseQuality convertBPNoiseQuality(noise::NoiseQuality quality) const;
	void UpdateOptions();

	//These are private as they should not be edited at runtime
	UPROPERTY(EditAnywhere, Category = "Perlin")
	float CustomFrequency = 1.0;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	float CustomLacunarity = 1.0;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	TEnumAsByte<qualities::PerlinNoiseQuality> CustomNoiseQuality = qualities::QUALITY_STD;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	int CustomOctaveCount = 6;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	float CustomPersistence = 0.5;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	int CustomSeed = 0;
	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY()
	USceneComponent* Root;

};
