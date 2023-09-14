#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"

UCLASS()
class CRYPTRAIDER_API AInteractableDoor : public AActor
{
	GENERATED_BODY()

private:
	UWorld* WorldPtr;

	UPROPERTY(EditAnywhere)
	FVector DetectionExtents;

public:
	// Sets default values for this actor's properties
	AInteractableDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
