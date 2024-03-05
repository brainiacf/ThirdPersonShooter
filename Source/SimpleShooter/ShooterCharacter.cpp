#include "ShooterCharacter.h"
#include "Rifle.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameModeBase.h"

AShooterCharacter::AShooterCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}


void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Rifle = GetWorld()->SpawnActor<ARifle>(RifleClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	Rifle->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	Rifle->SetOwner(this);
	Health = MaxHealth;
}


void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveRight",this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Pressed,this,&AShooterCharacter::Shoot);
}
void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}
// void AShooterCharacter::LookUp(float AxisValue)
// {
// 	AddControllerPitchInput(AxisValue);
// 

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}
void AShooterCharacter::Shoot()
{	
	Rifle->PullTrigger();
	//UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,BaseGunMesh,TEXT("MuzzleFlashSocket"));

}
float AShooterCharacter::TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health,DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp,Warning,TEXT("Health left %f"),Health);

	UE_LOG(LogTemp,Warning,TEXT("Ouch! I've been shot!"));
	if (IsDead()){

		AShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
		if(GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}


		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		
	

	}
	// if (Health==0)
	// {
	// 	Destroy();
	// }

	return DamageApplied;
}
bool AShooterCharacter::IsDead() const
{
	if(Health<=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}