// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostPawn.h"

void AGhostPawn::Hunt()
{
	State = EEnemyState::Default;

	StateChangedEvent.Broadcast(State);

}

void AGhostPawn::Idle()
{
	State = EEnemyState::Idle;

	StateChangedEvent.Broadcast(State);
}
