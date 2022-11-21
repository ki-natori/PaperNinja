// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PNFuncLibrary.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API UPNFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Math", BlueprintPure)
		static FVector FlattenVector(const FVector Vector);

	UFUNCTION(BlueprintCallable, Category = "Math", BlueprintPure)
		static FVector FlattenDirection(const FVector Vector);
};
