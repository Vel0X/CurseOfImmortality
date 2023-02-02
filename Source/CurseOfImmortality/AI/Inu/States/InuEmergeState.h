

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/AI/Inu/States/InuBaseState.h"
#include "InuEmergeState.generated.h"

/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API UInuEmergeState : public UInuBaseState
{
	GENERATED_BODY()
	
	virtual void OnStateEnter(UStateMachine* StateMachine) override;
	virtual void OnStateExit() override;
	virtual void OnStateUpdate(float DeltaTime) override;
};
