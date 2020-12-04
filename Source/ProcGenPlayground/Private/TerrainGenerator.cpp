// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGenerator.h"
#include <libnoise.h>

using namespace noise;

// Sets default values
ATerrainGenerator::ATerrainGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the default root object
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	//Initialize the proceduralization
	//UpdateOptions();
}

// Called when the game starts or when spawned
void ATerrainGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATerrainGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// *** Noise Property Getter / Setter FunctionsFunctions ***
float ATerrainGenerator::GetFrequency() const
{
	return perlinNoise.GetFrequency();
}

float ATerrainGenerator::GetLacunarity() const
{
	return perlinNoise.GetLacunarity();
}
qualities::PerlinNoiseQuality ATerrainGenerator::GetNoiseQuality() const
{
	return convertBPNoiseQuality(perlinNoise.GetNoiseQuality());
}

int ATerrainGenerator::GetOctaveCount() const
{
	return perlinNoise.GetOctaveCount();
}

float ATerrainGenerator::GetPersistence() const
{
	return perlinNoise.GetPersistence();
}

int ATerrainGenerator::GetSeed() const
{
	return perlinNoise.GetSeed();
}

int ATerrainGenerator::GetSourceModuleCount() const
{
	return perlinNoise.GetSourceModuleCount();
}

float ATerrainGenerator::GetValue(float x, float y, float z) const
{
	return perlinNoise.GetValue(x,y,z);
}
 
 //----------------------------------------------------------------------------------

void ATerrainGenerator::SetFrequency(float frequency)
{
	return perlinNoise.SetFrequency(frequency);
}

void ATerrainGenerator::SetLacunarity(float lacunarity)
{
	return perlinNoise.SetLacunarity(lacunarity);
}

void ATerrainGenerator::SetNoiseQuality(qualities::PerlinNoiseQuality noiseQuality)
{
	return perlinNoise.SetNoiseQuality(convertBPNoiseQuality(noiseQuality));
}

void ATerrainGenerator::SetOctaveCount(int octaveCount)
{
	perlinNoise.SetOctaveCount(octaveCount);
}

void ATerrainGenerator::SetPersistence(float persistence)
{
	perlinNoise.SetPersistence(persistence);
}

void ATerrainGenerator::SetSeed(int seed)
{
	perlinNoise.SetSeed(seed);
}

void ATerrainGenerator::SetRandomSeed()
{
	SetSeed(FMath::RandRange(0, 1000000));
}

void ATerrainGenerator::SetupOptions(float Frequency, float Lacunarity, qualities::PerlinNoiseQuality NoiseQuality, int OctaveCount, float Persistence, int Seed) 
{
	SetFrequency(Frequency);
	SetLacunarity(Lacunarity);
	SetNoiseQuality(NoiseQuality);
	SetOctaveCount(OctaveCount);
	SetPersistence(Persistence);
	SetSeed(Seed);
}

noise::NoiseQuality ATerrainGenerator::convertBPNoiseQuality(qualities::PerlinNoiseQuality quality) const
{
	switch (quality) {
	case qualities::QUALITY_FAST:
		return noise::QUALITY_FAST;
		break;
		break;
	case qualities::QUALITY_STD:
		return noise::QUALITY_STD;
		break;
	case qualities::QUALITY_BEST:
		return noise::QUALITY_BEST;
		break;
	default:
		return noise::QUALITY_STD;
	}
}

qualities::PerlinNoiseQuality ATerrainGenerator::convertBPNoiseQuality(noise::NoiseQuality quality) const
{
	switch (quality) {
	case noise::QUALITY_FAST:
		return qualities::QUALITY_FAST;
		break;
	case noise::QUALITY_STD:
		return qualities::QUALITY_STD;
		break;
	case noise::QUALITY_BEST:
		return qualities::QUALITY_BEST;
		break;
	default:
		return qualities::QUALITY_STD;
	}
}

void ATerrainGenerator::UpdateOptions()
{
	SetupOptions(CustomFrequency, CustomLacunarity, CustomNoiseQuality, CustomOctaveCount, CustomPersistence, CustomSeed);
}