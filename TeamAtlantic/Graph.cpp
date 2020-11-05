// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "Graph.h"

#include <cmath>
#include "EngineUtils.h"

// Sets default values
AGraph::AGraph()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGraph::BeginPlay()
{
	Super::BeginPlay();
	
	for (TObjectIterator<AVertex> Itr; Itr; ++Itr)
	{
		if (Itr->GetName().StartsWith("Vertex_BP")){
			AVertex *vertex = *Itr;
			int32 index = FCString::Atoi(*vertex->GetName().Mid(Itr->GetName().Len() - 2, 2));
			vertices[index] = vertex;

			if (index + 1 > maxVertices){
				maxVertices = index + 1;
			}

			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Itr->GetName());
			}
		}
	}
	
	for (TObjectIterator<AActor> Itr; Itr; ++Itr)
	{
		if (Itr->GetName().StartsWith("Patrol_BP")){
			AActor *actor = *Itr;
			int32 index = FCString::Atoi(*actor->GetName().Mid(Itr->GetName().Len() - 1, 1));
			patrol[index] = actor;

			if (index + 1 > maxPatrol){
				maxPatrol = index + 1;
			}

			if (GEngine)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Itr->GetName());
			}
		}
	}
	
	addEdge(vertices[0], vertices[1]);
	addEdge(vertices[1], vertices[2]);
	addEdge(vertices[2], vertices[3]);

	addEdge(vertices[4], vertices[5]);
	addEdge(vertices[5], vertices[6]);
	addEdge(vertices[6], vertices[7]);
	addEdge(vertices[7], vertices[8]);

	addEdge(vertices[0], vertices[4]);
	addEdge(vertices[0], vertices[5]);
	addEdge(vertices[1], vertices[5]);
	addEdge(vertices[1], vertices[6]);
	addEdge(vertices[2], vertices[6]);
	addEdge(vertices[2], vertices[7]);
	addEdge(vertices[3], vertices[7]);
	addEdge(vertices[3], vertices[8]);

	addEdge(vertices[4], vertices[9]);
	addEdge(vertices[5], vertices[9]);
	addEdge(vertices[7], vertices[10]);
	addEdge(vertices[8], vertices[10]);

	addEdge(vertices[9], vertices[11]);
	addEdge(vertices[9], vertices[12]);
	addEdge(vertices[10], vertices[14]);
	addEdge(vertices[10], vertices[15]);

	addEdge(vertices[11], vertices[12]);
	addEdge(vertices[12], vertices[13]);
	addEdge(vertices[13], vertices[14]);
	addEdge(vertices[14], vertices[15]);

	addEdge(vertices[16], vertices[17]);
	addEdge(vertices[17], vertices[18]);
	addEdge(vertices[18], vertices[19]);

	addEdge(vertices[11], vertices[16]);
	addEdge(vertices[12], vertices[16]);
	addEdge(vertices[12], vertices[17]);
	addEdge(vertices[13], vertices[17]);
	addEdge(vertices[13], vertices[17]);
	addEdge(vertices[14], vertices[18]);
	addEdge(vertices[14], vertices[18]);
	addEdge(vertices[15], vertices[19]);
	
	currentIndex = 0;
}

// Called every frame
void AGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGraph::addEdge(AVertex *v1, AVertex *v2){
	v1->addAdjVertex(v2);
	v2->addAdjVertex(v1);
}

float AGraph::getDistance(AVertex *v1, AVertex *v2){
	return sqrt(pow((v1->getX() - v2->getX()), 2) + pow((v1->getY() - v2->getY()), 2) + pow((v1->getZ() - v2->getZ()), 2));
}

float AGraph::getDistance(FVector v1, FVector v2){
	return sqrt(pow((v1.X - v2.X), 2) + pow((v1.Y - v2.Y), 2) + pow((v1.Z - v2.Z), 2));
}

vector<AVertex*> AGraph::shortestPath(AVertex *start, AVertex *goal){
	vector<AVertex*> open;
	vector<AVertex*> closed;

	for (int i = 0; i < maxVertices; i++){
		vertices[i]->setCosts(0, 0);
		vertices[i]->setParent(nullptr);
	}

	start->setCosts(0, getDistance(start, goal));

	open.push_back(start);

	while (open.size() > 0){
		AVertex *current = nullptr;
		float lowestCost = std::numeric_limits<float>::max();
		float lowestCostIndex = -1;

		for (int i = 0; i < open.size(); i++){
			if (open[i]->getF() < lowestCost){
				lowestCostIndex = i;
				lowestCost = open[i]->getF();
				current = open[i];
			}
		}

		if (current == goal){
			return reconstructPath(start, goal);
		}

		open.erase(open.begin() + lowestCostIndex);
		closed.push_back(current);
		vector<AVertex*> neighbors = current->getAdjVertex();

		for (int i = 0; i < neighbors.size(); i++){
			vector<AVertex*>::iterator itClosed = std::find(closed.begin(), closed.end(), neighbors[i]);
			vector<AVertex*>::iterator itOpen = std::find(open.begin(), open.end(), neighbors[i]);

			float tentativeG = current->getG() + getDistance(current, neighbors[i]);

			if (itClosed != closed.end() && tentativeG < neighbors[i]->getG()){
				neighbors[i]->setParent(current);
				neighbors[i]->setCosts(tentativeG, getDistance(neighbors[i], goal));
			}
			else if (itClosed != closed.end() && tentativeG < neighbors[i]->getG()){
				neighbors[i]->setParent(current);
				neighbors[i]->setCosts(tentativeG, getDistance(neighbors[i], goal));
			}
			else if (itClosed == closed.end() && itOpen == open.end()){
				neighbors[i]->setParent(current);
				neighbors[i]->setCosts(tentativeG, getDistance(neighbors[i], goal));
				open.push_back(neighbors[i]);
			}
		}
	}

	return reconstructPath(start, goal);
}

vector<AVertex*> AGraph::reconstructPath(AVertex *start, AVertex *goal){
	vector<AVertex*> pathBack;
	vector<AVertex*> path;
	AVertex *current = goal;

	pathBack.push_back(current);

	while (current->getParent() != NULL){
		pathBack.push_back(current->getParent());
		current = current->getParent();
	}

	if (current == start){
		for (int i = (int)pathBack.size() - 1; i >= 0; i--){
			path.push_back(pathBack[i]);
		}
	}

	return path;
}


AVertex *AGraph::getNext(){
	return vertices[maxVertices - 1];
}

AVertex *AGraph::getClosestVertex(FVector loc){
	AVertex *vertex = nullptr;
	float lowestDistance = std::numeric_limits<float>::max();

	for (int i = 0; i < maxVertices; i++){
		float currentDistance = getDistance(vertices[i]->GetActorLocation(), loc);

		if (currentDistance < lowestDistance){
			lowestDistance = currentDistance;
			vertex = vertices[i];
		}
	}

	return vertex;
}

FVector AGraph::getNextPoint(bool pursuing, bool arrived, FVector goal){
	FVector nextPoint;

	if (pursuing){
		if (arrived){
			currentIndex += 1;
		}

		if (currentIndex < shortestP.size()){
			nextPoint = shortestP[currentIndex]->GetActorLocation();
		}
		else{
			nextPoint = goal;
		}
	}
	else{
		if (arrived){
			currentIndex = (currentIndex + 1) % maxPatrol;
		}

		nextPoint = patrol[currentIndex]->GetActorLocation();
	}

	return nextPoint;
}

void AGraph::calcShortestPath(bool pursuing, FVector loc1, FVector loc2){

	if (pursuing){
		AVertex *start = getClosestVertex(loc1);
		AVertex *goal = getClosestVertex(loc2);

		currentIndex = 0;

		shortestP.clear();
		shortestP = shortestPath(start, goal);

		if (shortestP.size() > 0 && getDistance(shortestP[0]->GetActorLocation(), loc1) < 200){
			currentIndex = 1;
		}
	}
	else{

	}
}

void AGraph::switchMode(){
	currentIndex = 0;
}
