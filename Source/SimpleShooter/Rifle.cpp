#include "Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

ARifle::ARifle()
{
 	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BaseGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	BaseGunMesh->SetupAttachment(Root);
	FVector GunLocation(-0.759085f, -15.486331f, -2.251062f);
	BaseGunMesh->SetRelativeLocation(GunLocation);
}


void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARifle::PullTrigger()
{
	UE_LOG(LogTemp,Warning,TEXT("shootshoot"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,BaseGunMesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,BaseGunMesh,TEXT("MuzzleFlashSocket"));
	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = TraceingBullet(Hit,ShotDirection);
	if(bSuccess)
	{
		//DrawDebugPoint(GetWorld(),Hit.Location,20,FColor::Red,true);
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),SoundOnImpact,Hit.Location);
		AActor * HitActor = Hit.GetActor();
		
		if(HitActor!=nullptr)
		{
			FPointDamageEvent DamageEvent (Damage, Hit, ShotDirection, nullptr);

			AController *OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
			
		}
	
		
	}

}
bool ARifle::TraceingBullet(FHitResult &Hit,FVector &ShotDirection)
{
	AController *OwnerController = GetOwnerController();
	if(OwnerController==nullptr) return false;

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerController->GetPlayerViewPoint(CameraLocation,CameraRotation);
	ShotDirection = -CameraRotation.Vector();

	FVector End =CameraLocation+ CameraRotation.Vector()* MaxRangeRifle; 

	//DrawDebugCamera(GetWorld(),CameraLocation,CameraRotation,90,2,FColor::Red,true);	
	
	//Hit Start 
	Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit,CameraLocation,End,ECollisionChannel::ECC_GameTraceChannel1,Params);
	

}

AController* ARifle::GetOwnerController() const
{
	APawn*OwnerPawn=Cast<APawn>(GetOwner());
	if(OwnerPawn==nullptr) return nullptr;
	return OwnerPawn->GetController();
	
}


//(X=-0.759085,Y=-15.486331,Z=-2.251062)
