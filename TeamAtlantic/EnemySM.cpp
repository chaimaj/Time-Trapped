// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamAtlantic.h"
#include "EnemySM.h"

EnemySM::EnemySM()
{
	state = PATROLLING;
}

EnemySM::~EnemySM()
{
}

void EnemySM::update(EnemySignal sig){
	switch (state) {
	case PATROLLING:
		if (sig == SEES_CHARACTER){
			state = PURSUING;
		}
		break;
	case PURSUING:
		if (sig == CHARACTER_IN_SAFE_PLACE){
			state = PATROLLING;
		}
		break;

	default:
		break;
	}
}

EnemyState EnemySM::getState(){
	return state;
}
