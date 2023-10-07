#include "Interactables/InteractableDoor.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Components/InstancedStaticMeshComponent.h"

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
	DoorInstancedMesh = FindComponentByClass<UInstancedStaticMeshComponent>();
	TransitionDistance = FVector::Distance(ClosedStateLocation, OpenedStateLocation);
	if (DoorInstancedMesh == nullptr) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("ERROR: Door instance mesh not found!"));
	}
}

void AInteractableDoor::OpenDoor(float deltaTime)
{
	FVector curLoc = DoorInstancedMesh->GetRelativeLocation();
	FVector transitionDir = (OpenedStateLocation - ClosedStateLocation).GetSafeNormal();
	if (FVector::PointsAreNear(curLoc, OpenedStateLocation, 5.0f)) 
	{
		DoorInstancedMesh->SetRelativeLocation(OpenedStateLocation);
		bIsOpened = true;
		return;
	}
	DoorInstancedMesh->SetRelativeLocation(curLoc + transitionDir * TransitionSpeed * deltaTime);
}

void AInteractableDoor::CloseDoor(float deltaTime)
{
	FVector curLoc = DoorInstancedMesh->GetRelativeLocation();
	FVector transitionDir = (ClosedStateLocation - OpenedStateLocation).GetSafeNormal();
	if (FVector::PointsAreNear(curLoc, ClosedStateLocation, 5.0f))
	{
		DoorInstancedMesh->SetRelativeLocation(ClosedStateLocation);
		bIsOpened = false;
		return;
	}
	DoorInstancedMesh->SetRelativeLocation(curLoc + transitionDir * TransitionSpeed * deltaTime);
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
		if (!bIsTriggered)
		{
			bIsTriggered = true;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Camera next to door!"));
	}
	else 
	{
		if (bIsTriggered)
		{
			bIsTriggered = false;
		}
	}
	
	if (bIsTriggered) 
	{
		OpenDoor(DeltaTime);
	}
	else 
	{
		CloseDoor(DeltaTime);
	}
}
