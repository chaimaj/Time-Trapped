// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "MyEnemy.h"

#include "MyCompanion.h"


//Useful functions
//FVector Truncate(FVector velocity, float maxSpeed);
//float min(float a, float b);



// Sets default values
AMyEnemy::AMyEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	past = false;

}

AMyEnemy::AMyEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
	}
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
}

void AMyEnemy::switchMode(){
	switch (stateMachine.getState()){
	case PATROLLING:
		stateMachine.update(SEES_CHARACTER);
		break;
	case PURSUING:
		stateMachine.update(CHARACTER_IN_SAFE_PLACE);
		break;
	}
}

void AMyEnemy::togglePast(){
	past = !past;
}

bool AMyEnemy::isPast(){
	return past;
}

bool AMyEnemy::isPursuing(){
	return stateMachine.getState() == PURSUING;
}