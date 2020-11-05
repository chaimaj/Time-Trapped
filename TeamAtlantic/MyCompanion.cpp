// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "MyCompanion.h"


//Useful functions
FVector Truncate(FVector velocity, float maxSpeed);
float min(float a, float b);


// Sets default values
AMyCompanion::AMyCompanion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


AMyCompanion::AMyCompanion(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	//CollisionComp->BodyInstance.SetCollisionProfileName("Companion");
	CollisionComp->InitSphereRadius(15.0f);
	CollisionComp->SetSimulatePhysics(false);
	RootComponent = CollisionComp;
	Velocity = FVector(0.0f, 0.0f, 0.0f);
	// Use a ProjectileMovementComponent to govern this projectile's movement
	/*CompanionMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("CompanionComp"));
	CompanionMovement->UpdatedComponent = CollisionComp;
	CompanionMovement->InitialSpeed = 0.f;
	CompanionMovement->MaxSpeed = 3000.f;
	CompanionMovement->bRotationFollowsVelocity = true;
	CompanionMovement->bShouldBounce = true;
	CompanionMovement->Bounciness = 0.3f;*/

	// Die after 3 seconds by default
	//InitialLifeSpan = 3.0f;

}


// Called when the game starts or when spawned
void AMyCompanion::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AMyHero> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->IsA(AMyHero::StaticClass()))
		{
			AimActor = static_cast<AMyHero*>(*ActorItr);
		}
	}

}

// Called every frame
void AMyCompanion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector offset(-50, 30, 200);
	FVector Force = Pursuing(AimActor->GetActorLocation(), offset);
	//InitVelocity(Force);
	FVector acceleration = Force / 2.5f;
	Velocity += acceleration;

	//Truncating velocity
	Velocity = Truncate(Velocity, maxSpeed);

	FVector newPosition = this->GetActorLocation() + Velocity * DeltaTime;

	this->SetActorLocation(newPosition);
}



//Seek
FVector AMyCompanion::Seek(FVector target){
	// vector from here to target scaled by maxSpeed
	FVector desired = Truncate(target - GetActorLocation(), maxSpeed);

	// return steering force
	return desired - Velocity;  // vector difference
}

//Arrive
FVector AMyCompanion::Arrive(FVector target){
	FVector result(0.0f, 0.0f, 0.0f);
	FVector desired = (target - GetActorLocation());
	float distance = desired.Size();   // distance to target1
	if (distance == 0)  // if at target, stop
	{
		return result;
	}

	// slow down linearly with distance.
	// DECELERATION allows tweaking (larger is slower)
	float speed = distance / DECELERATION;

	// current speed cannot exceed maxSpeed
	speed = min(speed, maxSpeed);

	// vector from here to target scaled by speed
	desired = desired * speed / distance;

	// return steering force as in seek (note, if heading
	// directly at target already, this just decelerates)
	return desired - Velocity;
}

//Floating force
FVector AMyCompanion::Floating(float ForceAmount){
	FVector Force(0, 0, ForceAmount);
	return Force;
}

//Following the character
FVector AMyCompanion::Pursuing(FVector target, FVector offset){

	// calculate lookahead time based on distance and speeds
	float dt = abs((target - (GetActorLocation() + offset)).Size()) / (maxSpeed + abs(Velocity.Size()));
	// arrive at predicted offset position (vs. seek)
	return Arrive(target + offset);

}


FVector Truncate(FVector velocity, float maxSpeed) {
	if (velocity.Size() > maxSpeed)
	{
		velocity.Normalize();
		velocity *= maxSpeed;
	}
	return velocity;
}

float min(float a, float b){
	if (a < b){
		return a;
	}
	return b;
}
