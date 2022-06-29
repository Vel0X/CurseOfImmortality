// 

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CurseOfImmortality/UpgradeSystem/BaseClasses/BaseAbility.h"
#include "Chalice.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AChalice : public ABaseAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChalice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnHitNotify(ABaseCharacter* HitCharacter) override;
	
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* Vfx;
	
	UPROPERTY(EditAnywhere)
	float Cooldown = 20.0f;

	float CurrentCooldown = 0.1f;
};
