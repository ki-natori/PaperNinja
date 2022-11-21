
#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Test_Event_Gate.generated.h"

/**
 *
 */
UCLASS()
class PAPERNINJA_API ATest_Event_Gate : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ATest_Event_Gate();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
		void TurnOnSwitch();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class APNGateActor* GateActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class APNSwitchActor* SwitchActor;

	UPROPERTY(BlueprintReadWrite)
		FTimerHandle TimerHandle;
};
