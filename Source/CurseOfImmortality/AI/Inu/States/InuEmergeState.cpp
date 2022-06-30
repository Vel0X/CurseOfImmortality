#include "CurseOfImmortality/AI/Inu/States/InuEmergeState.h"

#include "CurseOfImmortality/AI/Inu/InuPawn.h"
#include "CurseOfImmortality/AI/Inu/InuStateMachine.h"
#include "CurseOfImmortality/Management/PersistentWorldManager.h"

void UInuEmergeState::OnStateEnter(UStateMachine* StateMachine)
{
	Super::OnStateEnter(StateMachine);

	Controller = Cast<UInuStateMachine>(StateMachine);
	Player = Controller->GetPlayer();
	SelfRef = Controller->GetSelfRef();

	SelfRef->Emerge = true;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Emerge State Entered"))
	}
}

void UInuEmergeState::OnStateExit()
{
	Super::OnStateExit();

	SelfRef->Emerge = false;
	if (FPersistentWorldManager::GetLogLevel(InuStateMachine))
	{
		UE_LOG(LogTemp, Warning, TEXT("Emerge State Exit"))
	}
}

void UInuEmergeState::OnStateUpdate(float DeltaTime)
{
	Super::OnStateUpdate(DeltaTime);

	if (SelfRef->AnimationStart)
	{
		SelfRef->GetRootComponent()->SetVisibility(true, true);
	}
	if (SelfRef->AnimationEnd)
	{
		Controller->Transition(Controller->Running, Controller);
	}
}
