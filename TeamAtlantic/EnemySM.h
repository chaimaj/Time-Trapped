// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

enum EnemyState {
	PATROLLING,
	PURSUING
};

enum EnemySignal {
	SEES_CHARACTER,
	CHARACTER_IN_SAFE_PLACE,
};

/**
 * 
 */
class TEAMATLANTIC_API EnemySM
{
	EnemyState state;

public:
	EnemySM();
	~EnemySM();

	void update(EnemySignal sig);
	EnemyState getState();
};
