// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "Vertex.h"

#include "GameFramework/Actor.h"
#include "Graph.generated.h"

using namespace std;

UCLASS()
class TEAMATLANTIC_API AGraph : public AActor
{
	GENERATED_BODY()

private:
	AVertex *vertices[100];
	int maxVertices;

	AActor *patrol[10];
	int maxPatrol;

	vector<AVertex*> shortestP;
	int currentIndex;

public:
	AGraph();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	vector<AVertex*> shortestPath(AVertex *start, AVertex *goal);
	vector<AVertex*> reconstructPath(AVertex *start, AVertex *goal);
	float getDistance(AVertex *v1, AVertex *v2);
	float getDistance(FVector v1, FVector v2);

	void addEdge(AVertex *v1, AVertex *v2);

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		AVertex *getNext();

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		AVertex *getClosestVertex(FVector loc);

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		FVector getNextPoint(bool pursuing, bool arrived, FVector goal);

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		void calcShortestPath(bool pursuing, FVector loc1, FVector loc2);

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		void switchMode();
};
