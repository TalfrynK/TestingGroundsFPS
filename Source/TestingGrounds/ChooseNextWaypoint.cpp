// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "PatrollingGuard.h"
#include "TestingGrounds.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIGuard = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIGuard->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	Index = Index + 1;
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index%PatrolPoints.Num());
	return EBTNodeResult::Succeeded;
}

