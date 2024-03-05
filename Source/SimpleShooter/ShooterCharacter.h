

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


class ARifle;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AShooterCharacter();

protected:
	
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, 
		struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, 
		AActor* DamageCauser);

	

public:	

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure) 
	bool IsDead() const;
	void Shoot();




private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	//void LookUp(float AxisValue);


	UPROPERTY(EditDefaultsOnly) // bcz i dont want to edit this at runtime
	TSubclassOf<ARifle>RifleClass;
	UPROPERTY()
	ARifle* Rifle;
	

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float Health;

};
