// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class AWizard;

UENUM(BlueprintType)
enum class ItemState : uint8 { NotEqquipped, Equipped };

UCLASS()
class MYOPENWORLDPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Equip(AWizard* Player, FName SocketName);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float SetRunningTime(float _runningTime) {runningTime = _runningTime; return runningTime;}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetRunningTime() {return runningTime;}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float SetMovementRate(float _movementRate) { movementRate = _movementRate; return movementRate;}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMovementRate() {return movementRate;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStaticMeshComponent* GetStaticMesh() {return ItemMesh;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMyItemState(ItemState _MyItemState) { MyItemState = _MyItemState;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ItemState GetMyItemState(){ return MyItemState;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SphereOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void SphereOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, Category="ITEM STATE")
	ItemState MyItemState;

private: 
	
	UPROPERTY(EditAnywhere, Category = "ItemProperty - Sine Values")		//BlueprintReadOnly , VisibleAnywhere, EditAnywhere , Category = "VALUE"
	float runningTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "ItemProperty - Movement Values")
	float movementRate = 200.0f;

	};