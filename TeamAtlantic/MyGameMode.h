// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEAMATLANTIC_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
	AMyGameMode(const FObjectInitializer& ObjectInitializer);  // Our added constructor

	virtual void StartPlay() override; // Note that engine version 4.3 changed this method's name to StartPlay(), because of this engine versions before 4.3, or older tutorials, use BeginPlay()

	
	
	
};
