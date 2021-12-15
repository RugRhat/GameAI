// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAI.h"
#include "TankAITask.h"

UENUM()
enum TaskType
{
  WANDER	UMETA(DisplayName = "Wander"), 
  RETREAT	UMETA(DisplayName = "Retreat"), 
  PURSUE	UMETA(DisplayName = "Pursue"), 
  HIDE		UMETA(DisplayName = "Hide"), 
  ATTACK	UMETA(DisplayName = "Attack")  
};

// Used by TaskPriorityPredicate to sort Tasks in queue based on priority
struct TaskPriority
{
	TankAITask* Task;
	int Priority;

	TaskPriority(TankAITask* _Task)
	{
		Task = _Task;
		Priority = Task->GetPriority();
	}

	TaskPriority()
	{
		Task = NULL;
		Priority = 0;
	}
};

// Used to sort Tasks in queue in ascending order based on priority
struct TaskPriorityPredicate
{
	bool operator() (const TaskPriority& A, const TaskPriority& B) const
	{
		return A.Priority < B.Priority;
	}
};

class SURVIVAL_API TaskManager
{

public:
	TaskManager(ATankAI* AIController);
	~TaskManager();

	void CheckParameters();
	void RunTask();
	void DestroyTasks();

	bool bTaskComplete;

	TEnumAsByte<TaskType> GetCurrentTaskType() { return CurrentTaskType; }

private:
	void AddTask(TaskType TaskType, TankAITask* Task);

	void UpdatePriorities();
	void StartNewTask();

	bool bPlayerInRange;
	bool bPlayerInFiringRange;
	bool bNeedToHeal;
	bool bAtFullHealth;
	bool bOtherAttackers;

	class HideTask* HideTaskRef;
	class PursueTask* PursueTaskRef;
	class AttackTask* AttackTaskRef;

	TEnumAsByte<TaskType> PrioritizeHiding();
	TEnumAsByte<TaskType> PrioritizeMovingToAttack();
	TEnumAsByte<TaskType> PrioritizeAttacking();

	bool bSafeToRunTask = false;
	
protected:
	TMap<TaskType, TankAITask*> TaskMap;

	TArray<TaskPriority> TaskPriorityQueue;

	ATankAI* TankController;

	TankAITask* CurrentTask;

	TEnumAsByte<TaskType> CurrentTaskType;

};
