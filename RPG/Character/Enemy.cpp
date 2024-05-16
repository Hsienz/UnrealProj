// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "RPG/Actor/Weapon.h"
#include "RPG/ActorComponents/LimitedValue/Health.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "RPG/GAS/AbilitySystemComponent/EnhancedAbilitySystemComponent.h"
#include "RPG/GAS/LimitedValue/HealthAttribute.h"
#include "RPG/Interfaces/HasMontageComponent.h"
#include "RPG/UserWidgets/StatusBar/StatusBarWidget.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	InfoWidgetComponent->SetupAttachment( RootComponent );

	AbilitySystemComponent = CreateDefaultSubobject<UEnhancedAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	HealthAttribute = CreateDefaultSubobject<UHealthAttribute>(TEXT("HealthAttribute"));

	MontageComponent = CreateDefaultSubobject<UMontageComponent>(TEXT("MontageComponent"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if( UStatusBarWidget* HealthStatus = Cast<UStatusBarWidget>( InfoWidgetComponent->GetUserWidgetObject() ) )
	{
		HealthStatus->SetActorRef( this );
	}
}

void AEnemy::HandleDead_Implementation()
{
	IDamageable::HandleDead_Implementation();
	GetCharacterMovement()->DisableMovement();
	InfoWidgetComponent->SetVisibility( false );
	if( AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->BrainComponent->StopLogic("Death");
	}
	if( DeadAnim )
	{
		MontageComponent->ServerMulticastMontagePlay( DeadAnim );
		FOnMontageEnded Delegate;
		Delegate.BindUObject( this, &AEnemy::DeadAnimEndDelegate );
		MontageComponent->GetAnimInstance()->Montage_SetEndDelegate( Delegate );
	}
	UE_LOG( LogTemp, Warning, TEXT("%s is dead"), *GetName() );
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	// below code seems broke on c++, see BP_Dummy Event AnyDamage for detail ( cannot assign magnitude )
	FGameplayEffectContextHandle Context = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle OutgoingSpec = GetAbilitySystemComponent()->MakeOutgoingSpec( Cast<AWeapon>(DamageCauser)->DealDamageEffect, 1, Context) ;
	
	FGameplayEffectSpecHandle Spec = UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
		OutgoingSpec,
		FGameplayTag::RequestGameplayTag( TEXT( "Event.Damage" ) ),
		-DamageAmount
		);
	UE_LOG( LogTemp, Log, TEXT("%f, %f"), DamageAmount, Spec.Data->GetSetByCallerMagnitude( FGameplayTag::RequestGameplayTag(TEXT("Event.Damage"))) );
	FActiveGameplayEffectHandle Handle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf( *Spec.Data );
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AbilitySystemComponentPtr = AbilitySystemComponent;

	AbilitySystemComponent->InitAbilityActorInfo( this, this );
	
	ApplyDefaultEffects();
	GiveDefaultAbilities();
}

UMontageComponent* AEnemy::GetMontageSystem_Implementation() const
{
	return MontageComponent;
}

void AEnemy::AfterDead_Implementation()
{
	SetActorEnableCollision(false);
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda( [this]{Destroy();} );
	GetWorldTimerManager().SetTimer( DeathTimerHandle, TimerDelegate, 3, false );
}

void AEnemy::DeadAnimEndDelegate(UAnimMontage* Anim, bool bIsInterrupt)
{
	SetActorEnableCollision( false );
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName( TEXT("Ragdoll" ) );
	Destroy();
}


// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UHealthAttribute* AEnemy::GetHealthAttribute_Implementation() const
{
	return HealthAttribute;
}

UWidgetComponent* AEnemy::GetInfoWidgetComponent() const
{
	return InfoWidgetComponent;
}

APatrolRoute* AEnemy::GetPatrolRoute_Implementation()
{
	return PatrolRoute;
}

