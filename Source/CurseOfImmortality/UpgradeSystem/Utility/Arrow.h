// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class APlayerCharacter;
class UNiagaraComponent;
UCLASS()
class CURSEOFIMMORTALITY_API AArrow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* ArrowPivot;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* Arrow;

	UPROPERTY()
	APlayerCharacter* Pc;
};
