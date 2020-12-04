// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h" 
#include "Engine/Texture2D.h" 
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "PerlinTest.generated.h"
USTRUCT()
struct FColumn {
	GENERATED_BODY()

		UPROPERTY()
		TArray<float> row;
};

UCLASS()
class PROCGENPLAYGROUND_API APerlinTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinTest();

	//Components
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	int customMapWidth;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	int customMapHeight;

	UPROPERTY(EditAnywhere, Category = "Perlin")
	float customNoiseScale = 0.3; //Don't default to a whole number, as it'll result in a constant of the same value

	UPROPERTY(EditAnywhere, Category = "Perlin")
	UTexture2D* noiseTexture;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	//QUESTION: Why does this section allow public referencing?

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Perlin")
	AStaticMeshActor* NoiseTestObject;
	

private:	
	UFUNCTION(CallInEditor, Category = "Perlin")
	void GenerateMap();
	
	TArray<FColumn> GenerateNoiseMap(int mapWidth, int mapHeight, float scale, int octaves, float persistance, float lacunarity);
	void DrawNoiseMap(TArray<FColumn> noiseMap);
};
