// Fill out your copyright notice in the Description page of Project Settings.

#include <libnoise.h>
#include "AssetRegistryModule.h"
#include "Materials/Material.h" 
#include "ImageUtils.h"
#include "PerlinTest.h"

// Sets default values
APerlinTest::APerlinTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Create the default root object
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void APerlinTest::BeginPlay()
{
	Super::BeginPlay();
	//GenerateNoiseMap(customMapWidth, customMapHeight, customNoiseScale);
}

// Called every frame
void APerlinTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

///GENERATE THE PERLIN NOISE DATA///
TArray<FColumn> APerlinTest::GenerateNoiseMap(int mapWidth, int mapHeight, float scale, int octaves, float persistance, float lacunarity) {
	UE_LOG(LogTemp, Warning, TEXT("Generating Noise Map..."));

	//Clamp zero values
	if (scale <= 0) {
		scale = 0.0001f;
	}
	
	TArray<FColumn> noiseMap;

	//Initialize the TArray columns
	noiseMap.AddDefaulted(mapWidth);
	UE_LOG(LogTemp, Warning, TEXT("Initiated %d columns"), mapWidth);

	//Initialize the TArray rows
	for(int x = 0; x < noiseMap.Num(); x++)
	{
		noiseMap[x].row.AddDefaulted(mapHeight);
		UE_LOG(LogTemp, Warning, TEXT("Initialized new row"));
	}
	
	float maxNoiseHeight = float.

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {

			float amplitude = 1;
			float frequency = 1;
			float noiseHeight = 0;

			for(int i = 0; i < octaves; i++){
				float sampleX = x / scale;
				float sampleY = y / scale;
			
			
				//Generate a 2D perlin noise value, and add it to our noise map
				float perlinValue = FMath::PerlinNoise2D(FVector2D(sampleX, sampleY) * 2 - 1);
				noiseHeight += perlinValue * amplitude;

				amplitude *= persistance;
				frequency *= lacunarity;

				UE_LOG(LogTemp, Warning, TEXT("Color Value: %d"), perlinValue);
			}

			noiseMap[x].row[y] = noiseHeight;
		}
	}
	
	return noiseMap;
}

///GENERATE THE MAP///
void APerlinTest::GenerateMap()
{
	TArray<FColumn> noiseMap = GenerateNoiseMap(customMapWidth, customMapHeight, customNoiseScale);
	int size = noiseMap[0].row.Num();
	UE_LOG(LogTemp, Warning, TEXT("Size: %d"), size);
	DrawNoiseMap(noiseMap);

}

///DRAW THE NOISE TEXTURE///
void APerlinTest::DrawNoiseMap(TArray<FColumn> noiseMap)
{
	int width = noiseMap.Num(); //Get length of columns
	int height = noiseMap[0].row.Num(); //Get length of rows (Using the first element as example)

	
	TArray<FColor> colorMap;
	colorMap.AddDefaulted(width * height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			FLinearColor generatedNoiseColor = FLinearColor::LerpUsingHSV(FColor::Black, FColor::White, noiseMap[x].row[y]);
			colorMap[y * width + x] = generatedNoiseColor.ToFColor(false);
		}
	}
	
	//Create the package (needed for saving)
	FString TextureName = TEXT("Test_Noise_Texture");
	FString PackageName = TEXT("/Game/ProceduralTextures/") + TextureName;
	UPackage* Package = CreatePackage(NULL, *PackageName);
	Package->FullyLoad();

	
	//Create the texture, assigning it to the package
	//RF_Public: Makes the asset able to be recognized by the editor once the package is saved
	//RF_Standalone: Makes the asset able to be used as a texture sample
	UTexture2D* testTexture = FImageUtils::CreateTexture2D(width, height, colorMap, Package, *TextureName, RF_Public | RF_Standalone, FCreateTexture2DParameters());
	
	//Update package and asset registry of the new asset
	Package->MarkPackageDirty();
	FAssetRegistryModule::AssetCreated(testTexture);

	//Save the package
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	bool didSave = UPackage::SavePackage(Package, testTexture, RF_Public | RF_Standalone, *PackageFileName);
	UE_LOG(LogTemp, Warning, TEXT("Successfully Created Noise Texture"));
	
	//Assign to test model
	UStaticMeshComponent* mesh = NoiseTestObject->GetStaticMeshComponent();
	UMaterial* meshMat = mesh->GetMaterial(0)->GetMaterial();
	meshMat->SetTextureParameterValueEditorOnly(TEXT("NoiseTexture"), testTexture);
	meshMat->PostEditChange();
	
}