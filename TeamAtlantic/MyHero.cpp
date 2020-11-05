// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "MyHero.h"

#include "MyCompanion.h"


//Useful functions
//FVector Truncate(FVector velocity, float maxSpeed);
//float min(float a, float b);



// Sets default values
AMyHero::AMyHero()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMyHero::AMyHero(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

//******* Getters and Setters**********//
void AMyHero::setMass(float new_mass){
	mass = new_mass;

}

float AMyHero::getMass(){
	return mass;
}

void AMyHero::setPosition(FVector new_position){
	position = new_position;
}

FVector AMyHero::getPosition(){
	return position;
}

void AMyHero::setVelocity(FVector new_velocity){
	velocity = new_velocity;
}

FVector AMyHero::getVelocity(){
	return velocity;
}

void AMyHero::setHeading(FVector new_heading){
	heading = new_heading;
}

FVector AMyHero::getHeading(){
	return heading;
}

void AMyHero::setMaxForce(float new_maxForce){
	maxForce = new_maxForce;
}

float AMyHero::getMaxForce(){
	return maxForce;
}

void AMyHero::setMaxSpeed(float new_maxSpeed){
	maxSpeed = new_maxSpeed;
}

float AMyHero::getMaxSpeed(){
	return maxSpeed;
}

// Called when the game starts or when spawned
void AMyHero::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this;
		//SpawnParams.Instigator = Instigator;
		FVector const MuzzleLocation = GetActorLocation() + CompanionOffset;
		FRotator MuzzleRotation = GetActorRotation();
		// spawn the projectile at the muzzle
		AMyCompanion* companion = World->SpawnActor<AMyCompanion>(CompanionClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	}
	setVelocity(FVector(0.0f, 0.0f, 0.0f));
	setMass(80);
}

// Called every frame
void AMyHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newPosition = this->GetActorLocation() + getVelocity() * DeltaTime;

	this->SetActorLocation(newPosition);

}

// Called to bind functionality to input
void AMyHero::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{

	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AMyHero::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyHero::MoveRight);
	InputComponent->BindAxis("Turn", this, &AMyHero::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMyHero::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyHero::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyHero::OnStopJump);

}

//Add force
void AMyHero::AddUpwardForce(float Force) {
	FVector force(Force, 0.0f, 0.0f);
	FName bone;
	GetCharacterMovement()->AddForce(force);
}


void AMyHero::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
	// find out which way is forward
	FRotator Rotation = Controller->GetControlRotation();
	// Limit pitch when walking or falling
	if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
	{
	Rotation.Pitch = 0.0f;
	}
	// add movement in that direction
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
	//AddUpwardForce(Value * 2000.0f);
	}
	// find out which way is forward
	/*FRotator Rotation = Controller->GetControlRotation();
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	FVector desired = Truncate(Direction - GetActorLocation(), maxSpeed);
	FVector steering = desired - getVelocity();
	FVector acceleration = steering / getMass();
	setVelocity(getVelocity() + acceleration);
	//Truncating velocity
	setVelocity(Truncate(getVelocity(), maxSpeed));*/

}

void AMyHero::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		//AddUpwardForce(Value * 2000.0f);
	}
}

void AMyHero::OnStartJump()
{
	bPressedJump = true;
}
void AMyHero::OnStopJump()
{
	bPressedJump = false;
}


