// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "MyGameMode.h"


#include "MyHero.h"

#include "Engine.h" //for version 4.4+

AMyGameMode::AMyGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	DefaultPawnClass = AMyHero::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/MyHero_BP.MyHero_BP_C'"));
	if (PlayerPawnObject.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
	StartMatch();
}

