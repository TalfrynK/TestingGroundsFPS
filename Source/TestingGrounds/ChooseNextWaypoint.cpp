// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "PatrolRoute.h"
#include "TestingGrounds.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	

	//Protecting against no Patrol Points
		
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	//Protecting against no PatrolRoute Compnent
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points Detected!"));
		return EBTNodeResult::Failed;
	}

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	Index = Index + 1;
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index%PatrolPoints.Num());
	return EBTNodeResult::Succeeded;
}

