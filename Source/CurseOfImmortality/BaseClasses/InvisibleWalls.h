

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InvisibleWalls.generated.h"

UCLASS()
class CURSEOFIMMORTALITY_API AInvisibleWalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvisibleWalls();

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
