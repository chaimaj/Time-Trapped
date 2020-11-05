// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "GameFramework/Actor.h"
#include "Vertex.generated.h"

UCLASS()
class TEAMATLANTIC_API AVertex : public AActor
{
	GENERATED_BODY()

private:
	float gCost;
	float hCost;

	std::vector<AVertex*> adjacent;
	AVertex *parent;

public:
	// Sets default values for this actor's properties
	AVertex();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void setPosition(float x, float y, float z);
	void setCosts(float g, float h);

	int getId();

	float getX();
	float getY();
	float getZ();

	float getF();
	float getG();
	float getH();

	AVertex *getParent();
	void setParent(AVertex *v);

	void addAdjVertex(AVertex *v);
	std::vector<AVertex*> getAdjVertex();
};
