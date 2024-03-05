// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay(   );
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        FVector StartLocation = GetPawn()->GetActorLocation();

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),StartLocation);
    }

    
    
}
void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
   
}

bool AShooterAIController::IsDead()const
{
    AShooterCharacter *ControllerCharacter = Cast<AShooterCharacter> (GetPawn());
    if(ControllerCharacter != nullptr)
    {
        return ControllerCharacter->IsDead();
    }

    return true;

}