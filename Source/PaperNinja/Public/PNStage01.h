
#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PNStage01.generated.h"

class APNGateActor;
class APNSwitchActor;

/**
 *
 */
UCLASS()
class PAPERNINJA_API APNStage01 : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	APNStage01();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OpenFusuma02();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		APNGateActor* Fusuma01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		APNSwitchActor* Fusuma01_SW;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		APNGateActor* Fusuma02;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		APNSwitchActor* Fusuma02_SW;

	UPROPERTY(BlueprintReadWrite)
		FTimerHandle TimerHandle;
};
