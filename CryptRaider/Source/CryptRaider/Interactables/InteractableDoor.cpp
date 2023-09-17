#include "InteractableDoor.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

// Sets default values
AInteractableDoor::AInteractableDoor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
	WorldPtr = GetWorld();
}

// Called every frame
void AInteractableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector originLoc = GetTransform().GetLocation() + DetectionOrigin;
	DrawDebugBox(WorldPtr, originLoc, DetectionExtents, FColor::Cyan, false, -1.0f, 0U, 20.0f);
	DrawDebugBox(WorldPtr, originLoc, FVector(10, 10, 10), FColor::Magenta, false, -1.0f, 0U, 20.0f);
	TArray<FOverlapResult> hits;
	if (WorldPtr->OverlapAnyTestByObjectType(originLoc, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeBox(DetectionExtents * 0.5f)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Camera next to door!"));
	}
	
}
