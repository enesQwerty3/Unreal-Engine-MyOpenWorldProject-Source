// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Characters/Wizard.h"

// Sets default values
AItem::AItem()
{
	MyItemState = ItemState::NotEqquipped;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));  //unreal factory method
	SetRootComponent(ItemMesh);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereCollision"));
	SphereCollision->SetupAttachment(RootComponent);
		
}
	 
// Called when the game starts or when spawned
void AItem::BeginPlay(){
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::SphereOnComponentBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::SphereOnComponentEndOverlap);

}


// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetRunningTime(this->runningTime + DeltaTime);
	FString Message = FString::Printf(TEXT("RunningTime: %f - DeltaTime: %f - Sin(100): %f"), this->runningTime, DeltaTime, FMath::Sin(100.0f));
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Green, Message);  //print running time as on screen message
	}

	/*
	FVector actorLocation = GetActorLocation();
	UWorld* world = GetWorld();

	if (world) {
		DrawDebugSphere(world, actorLocation, 100, 24, FColor::Red, false, -1.0f, (uint8)0U, 1.0f);
	}

		//movementRate (cm/s) * DeltaTime (s/frame) -> by this formula movement depends on frame but not how much of frame
	//SetActorLocation(actorLocation + (actorLocation.ForwardVector + actorLocation.RightVector) * movementRate * DeltaTime);
	SetActorLocation(actorLocation + (actorLocation.UpVector * FMath::Sin(this->runningTime) * 0.25f) + (actorLocation.ForwardVector * this->movementRate * DeltaTime));
									//sinusoidal wave movement											//forward movement
	*/

}


void AItem::SphereOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString OtherActorName(OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap - Other Actor Name: %s"), *OtherActorName);
}

void AItem::SphereOnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	FString OtherActorName(OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("End Overlap - Other Actor Name: %s"), *OtherActorName);
}


void AItem::Equip(AWizard* Player, FName SocketName)
{

}