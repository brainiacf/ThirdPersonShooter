// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if(PlayerController!=nullptr)
    {
       EndGame(false);
    }

    for(AShooterAIController *ControllerAI :TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!ControllerAI->IsDead())
        {
            return;
        }

    }
    
    EndGame(true);
    
}
void AKillEmAllGameMode::EndGame(bool bPlayerWin)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {   
        bool bIsWinner = Controller->IsPlayerController() == bPlayerWin;
        Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
    }
}

