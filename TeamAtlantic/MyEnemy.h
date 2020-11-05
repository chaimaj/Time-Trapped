// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemySM.h"

#include "GameFramework/Character.h"
#include "MyEnemy.generated.h"

UCLASS()
class TEAMATLANTIC_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	EnemySM stateMachine;
	float mass;

	bool past;

public:
	// Sets default values for this character's properties
	AMyEnemy();

	// Constructor for Player
	AMyEnemy(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		void switchMode();

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		void togglePast();

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		bool isPast();

	UFUNCTION(BlueprintCallable, Category = MyUUserWidgetClass)
		bool isPursuing();
};
