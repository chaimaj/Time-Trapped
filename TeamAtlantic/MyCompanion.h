// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyHero.h"

#include "GameFramework/Actor.h"
#include "MyCompanion.generated.h"

UCLASS()
class TEAMATLANTIC_API AMyCompanion : public AActor
{
	GENERATED_BODY()
	
public:

	float DECELERATION = 0.6f;
	FVector Velocity;
	AMyHero* AimActor;
	float maxSpeed = 500.0f;

	// Sets default values for this actor's properties
	AMyCompanion();


	AMyCompanion(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** inits velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);

	//Floating force
	FVector Floating(float ForceAmount);

	//Following the character
	FVector Pursuing(FVector target, FVector offset);

	//Seek
	FVector Seek(FVector target);

	//Arrive
	FVector Arrive(FVector target);


	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		UProjectileMovementComponent* CompanionMovement;

	/** Companion class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		TSubclassOf<class AMyHero> CharacterClass;

	
	
};
