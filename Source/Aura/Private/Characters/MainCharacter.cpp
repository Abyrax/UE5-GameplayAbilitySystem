// copyright abyrax


#include "Characters/MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MainPlayerState.h"

AMainCharacter::AMainCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f); 
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();	//for server
}

void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo(); // for client
}

void AMainCharacter::InitAbilityActorInfo()
{
	AMainPlayerState* MainPlayerState = GetPlayerState<AMainPlayerState>();
	check(MainPlayerState);
	MainPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MainPlayerState,this);
	AbilitySystemComponent = MainPlayerState->GetAbilitySystemComponent();
	AttributeSet = MainPlayerState->GetAttributeSet();
}
