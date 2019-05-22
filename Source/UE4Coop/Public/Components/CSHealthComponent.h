// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UCSHealthComponent*, HealthComp, float, Health, float, Damage, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4COOP_API UCSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    bool bIsDead;

    UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category="HealthComponent")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthComponent")
    float MaxHealth;

    UFUNCTION()
    void OnDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION()
    void OnRep_Health(float OldHealth);

 public:
    float GetHealth() const;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "HealthComponent")
    void ApplyHeal(float HealAmount);
};
