

#pragma once

#include "CoreMinimal.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "Stomping.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class CURSEOFIMMORTALITY_API AStomping : public ABaseAbility
{
	GENERATED_BODY()
	AStomping();

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere)
	float DamageWindow = 0.25f;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;
};
