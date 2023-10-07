#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"

UCLASS()
class CRYPTRAIDER_API AInteractableDoor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	float TransitionSpeed = 50.f;
	
	UPROPERTY(EditDefaultsOnly)
	FVector DetectionOrigin;

	UPROPERTY(EditDefaultsOnly)
	FVector DetectionExtents;

	UPROPERTY(EditDefaultsOnly)
	FVector OpenedStateLocation;

	bool bIsTriggered;
	float TransitionDistance;
	FVector ClosedStateLocation;
	class UInstancedStaticMeshComponent* DoorInstancedMesh;
	UWorld* WorldPtr;


public:

	bool bIsOpened = false;

	// Sets default values for this actor's properties
	AInteractableDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OpenDoor(float deltaTime);
	virtual void CloseDoor(float deltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
