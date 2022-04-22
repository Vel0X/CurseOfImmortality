// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackManager.h"
#include "GameController.h"

//#define GAME_INSTANCE static_cast<UGameController*>(GetGameInstance())

// Sets default values
AAttackManager::AAttackManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAttackManager::BeginPlay()
{
	Super::BeginPlay();
	BindToInput();
	static_cast<UGameController*>(GetGameInstance())->BindAbilityController(this);

}

void AAttackManager::CleanupAbility(int AbilityHandle)
{
	ActiveAbilities.Remove(AbilityHandle);
	UE_LOG(LogTemp, Warning, TEXT("Removed AbilityInstance from List. Remaining are %d abilities"), ActiveAbilities.Num());

}

// Called every frame
void AAttackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAttackManager::BindToInput() 
{
	// Initialize our component
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		// Bind inputs here
		// InputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealisticPawn::Jump);
		// etc...
		InputComponent->BindAction("TestInputZ", IE_Pressed, this, &AAttackManager::OnKeyPressed);	

		// Now hook up our InputComponent to one in a Player
		// Controller, so that input flows down to us
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AAttackManager::SpawnFromTemplate(ABaseAbility* Template) const
{
	const FVector Location = Template->GetActorLocation();
	const FRotator Rotation = Template->GetActorRotation();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.Template = Template;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template->GetClass(), &Location, &Rotation, Parameters));
	AbilityInstance->SetActorLocation(Template->GetActorLocation());

	//UE_LOG(LogTemp, Error, TEXT("Location of Original %s"), *Template->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Error, TEXT("Location after Spawning %s"), *AbilityInstance->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("templated Spawn was triggered"));

	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
}

void AAttackManager::SpawnFromTemplate(ABaseAbility* Template, const FRotator Rotator) const
{
	const FVector Location = Template->GetActorLocation();
	FActorSpawnParameters Parameters = FActorSpawnParameters();
	Parameters.Template = Template;
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(Template->GetClass(), &Location, &Rotator, Parameters));
	AbilityInstance->SetActorLocation(Template->GetActorLocation());
	//UE_LOG(LogTemp, Error, TEXT("Location of Original %s"), *Template->GetActorLocation().ToString());
	//UE_LOG(LogTemp, Error, TEXT("Location after Spawning %s"), *AbilityInstance->GetActorLocation().ToString());
	
	AbilityInstance->ResetLifetime();
	AbilityInstance->AfterInitialization();
	UE_LOG(LogTemp, Warning, TEXT("templated Spawn was triggered"));
}


void AAttackManager::OnKeyPressed()
{
	//ABaseAbility* baseAbilityInstance = (ABaseAbility*) GetWorld()->SpawnActor(ABaseAbility::StaticClass());
	ABaseAbility* AbilityInstance = static_cast<ABaseAbility*>(GetWorld()->SpawnActor(abilityClassType));
	AbilityInstance->InitializeAbility(AbilityMapHandle);
	
	for (const auto Upgrade : Upgrades)
	{
		AbilityInstance->AddUpgrade(Upgrade);
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawn was triggered"));
	AbilityInstance->AfterInitialization();

	//const FActiveAbility ActiveAbility = FActiveAbility(AbilityInstance, ActiveUpgrades);
	//ActiveAbilities.Add(AbilityMapHandle, ActiveAbility);
	AbilityMapHandle++;
	//UWorld::SpawnActor(abilityClassType);
}

