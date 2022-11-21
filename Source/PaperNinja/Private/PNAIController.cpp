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

	ConstructorHelpers::FObjectFinder<UBlackboardData> BlackBoardFinder(TEXT("BlackboardData'/Game/AI/PNBlackboard_Enemy.PNBlackboard_Enemy'"));
	if (BlackBoardFinder.Succeeded())
		UseBlackboard(BlackBoardFinder.Object, BlackboardComp);
	BlackboardComp->SetValueAsFloat(TEXT("PatrolWaitDuration"), ControlledPawn->PatrolWaitDuration);

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTFinder(TEXT("BehaviorTree'/Game/AI/PNBT_Patrol.PNBT_Patrol'"));
	if (BTFinder.Succeeded())
		RunBehaviorTree(BTFinder.Object);
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