// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyHero.generated.h"

UCLASS()
class TEAMATLANTIC_API AMyHero : public ACharacter
{
	GENERATED_BODY()

private:
	float mass;
	FVector position;
	FVector velocity;

	// orientation of body
	FVector heading;

	// dynamic properties of body
	float	maxForce;     // scalar
	float	maxSpeed;    // scalar


public:
	//Getters and setters
	void setMass(float new_mass);
	float getMass();
	void setPosition(FVector new_position);
	FVector getPosition();
	void setVelocity(FVector new_velocity);
	FVector getVelocity();
	void setHeading(FVector new_heading);
	FVector getHeading();
	void setMaxForce(float new_maxForce);
	float getMaxForce();
	void setMaxSpeed(float new_maxSpeed);
	float getMaxSpeed();



	// Sets default values for this character's properties
	AMyHero();

	// Constructor for Player
	AMyHero(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Add a force
	void AddUpwardForce(float ForceAmount);

	//handles moving forward/backward
	UFUNCTION()
		void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
		void MoveRight(float Val);

	//sets jump flag when key is pressed
	UFUNCTION()
		void OnStartJump();
	//clears jump flag when key is released
	UFUNCTION()
		void OnStopJump();

	/** Companion's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector CompanionOffset;

	/** Companion class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AMyCompanion> CompanionClass;
	
};
