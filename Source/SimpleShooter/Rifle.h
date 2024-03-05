#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class SIMPLESHOOTER_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	

	ARifle();

	void PullTrigger();

protected:
	
	virtual void BeginPlay() override;
	

public:	

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BaseGunMesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem*MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	
	UPROPERTY(EditAnywhere)
	USoundBase* SoundOnImpact;

	UPROPERTY(EditAnywhere)
	UParticleSystem*ImpactEffect;
	UPROPERTY(EditAnywhere)
	float Damage=10.0f;
	
	UPROPERTY(EditAnywhere)
	float MaxRangeRifle=1000.0f;


	bool TraceingBullet(FHitResult &Hit, FVector &ShotDirection);
	AController* GetOwnerController() const;
};
