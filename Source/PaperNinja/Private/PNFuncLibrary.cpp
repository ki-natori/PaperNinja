// Fill out your copyright notice in the Description page of Project Settings.


#include "PNFuncLibrary.h"

FVector UPNFuncLibrary::FlattenVector(const FVector Vector)
{
	return FVector(Vector.X, Vector.Y, 0.0);
}

FVector UPNFuncLibrary::FlattenDirection(const FVector Vector)
{
	FVector FlattenedVector = FlattenVector(Vector);
	FlattenedVector.Normalize();
	return FlattenedVector;
}