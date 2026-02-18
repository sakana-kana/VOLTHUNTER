//íSìñç≤ÅXñÿëtëæ
//çUåÇè’ìÀîªíËÉNÉâÉX

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackCollisionFactory.generated.h"

class AAttackCollisionDetection;

UCLASS()
class HIGHSPEEDACTIONGAME_API AAttackCollisionFactory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAttackCollisionFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TObjectPtr<AAttackCollisionDetection> CreateAAttackCollisionDetection(UWorld* World, const FVector& Location, const FRotator& Rotation)const;

	UPROPERTY(EditAnywhere, Category = "AttackCollisionDetection")
	TSubclassOf<AAttackCollisionDetection> AttackCollisionClass;

};
