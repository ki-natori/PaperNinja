// Fill out your copyright notice in the Description page of Project Settings.


#include "PNAIController.h"
#include "PNPawn_Rabbit.h"
#include "BehaviorTree/Behaviortree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

APNAIController::APNAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	PatrolIndex = 0;
}

void APNAIController::BeginPlay()
{
	Super::BeginPlay();

	APNPawn_Rabbit* ControlledPawn = CastChecked<APNPawn_Rabbit>(GetPawn());
	if (ControlledPawn->PatrolPoints.Num())
		AI_PatrollPoints = ControlledPawn->PatrolPoints;

	UBlackboardData* BlackBoard = LoadObject<UBlackboardData>(NULL, TEXT("BlackboardData'/Game/AI/PNBlackboard_Enemy.PNBlackboard_Enemy'"));
	if (BlackBoard)
		UseBlackboard(BlackBoard, BlackboardComp);
	BlackboardComp->SetValueAsFloat(TEXT("PatrolWaitDuration"), ControlledPawn->PatrolWaitDuration);

	UBehaviorTree* BehaviorTree = LoadObject<UBehaviorTree>(NULL, TEXT("BehaviorTree'/Game/AI/PNBT_Patrol.PNBT_Patrol'"));
	if (BehaviorTree)
		RunBehaviorTree(BehaviorTree);
}

FVector APNAIController::GetPatrolLocation() const
{
	if (AI_PatrollPoints.Num())
		return AI_PatrollPoints[PatrolIndex]->GetActorLocation();

	return FVector::Zero();
}

void APNAIController::PopPatrolLocation()
{
	PatrolIndex++;
	PatrolIndex %= AI_PatrollPoints.Num();
}

void APNAIController::GoToPatrol()
{
	MoveTo(GetPatrolLocation());
}