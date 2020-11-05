// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "Vertex.h"

// Sets default values
AVertex::AVertex()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVertex::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVertex::setCosts(float g, float h){
	this->gCost = g;
	this->hCost = h;
}

float AVertex::getX(){
	return GetActorLocation().X;
}

float AVertex::getY(){
	return GetActorLocation().Y;
}

float AVertex::getZ(){
	return GetActorLocation().Z;
}

float AVertex::getF(){
	return gCost + hCost;
}

float AVertex::getG(){
	return gCost;
}

float AVertex::getH(){
	return hCost;
}

AVertex *AVertex::getParent(){
	return parent;
}

void AVertex::setParent(AVertex *v){
	this->parent = v;
}

void AVertex::addAdjVertex(AVertex *v){
	adjacent.push_back(v);
}

std::vector<AVertex*> AVertex::getAdjVertex(){
	return adjacent;
}

