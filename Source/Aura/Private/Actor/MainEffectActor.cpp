// copyright abyrax


#include "Actor/MainEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/MainAttributeSet.h"
#include "Components/SphereComponent.h"

AMainEffectActor::AMainEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AMainEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//todo: will be changed to apply gameplay effect.
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UMainAttributeSet* MainAttributeSet = Cast<UMainAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UMainAttributeSet::StaticClass()));
		UMainAttributeSet* MutableMainAttributeSet = const_cast<UMainAttributeSet*>(MainAttributeSet);
		MutableMainAttributeSet->SetHealth(MainAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AMainEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AMainEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMainEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMainEffectActor::EndOverlap);
}


