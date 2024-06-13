// copyright abyrax

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMainCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	void InitAbilityActorInfo();
};
