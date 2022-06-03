#pragma once

#include "CoreMinimal.h"
#include "DamageFormula.generated.h"

USTRUCT()
struct FDamageFormula
{
	GENERATED_BODY()

	/** How much Damage is done, disregarding player stats */
	UPROPERTY(EditAnywhere)
	float BaseDamage;
	
	/** How much of the AttackDamage Stat gets added on top of the damage */
	UPROPERTY(EditAnywhere, meta=(UIMin = 0.0f, UIMax = 1.0f))
	float ScaleFactor;

	/** How much the total damage varies from hit to hit */
	UPROPERTY(EditAnywhere, meta=(UIMin = 0.0f, UIMax = 1.0f))
	float Variation;
};