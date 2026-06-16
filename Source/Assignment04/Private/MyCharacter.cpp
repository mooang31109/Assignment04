// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "IEditableSkeleton.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(false);
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetSimulatePhysics(false);
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp-> SetupAttachment(RootComponent);
	SpringArmComp-> TargetArmLength = 300.0f;
	SpringArmComp -> bUsePawnControlRotation = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp -> bUsePawnControlRotation = false;
	
	MovementSpeed = 300.0f;
	RotationSpeed = 45.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController -> MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController -> MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCharacter::Move
					);
			}
			
			if (PlayerController -> LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController -> LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCharacter::Look
					);
			}
		}
	}
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	const FVector Forward = GetActorForwardVector();
	const FVector Right = GetActorRightVector();
	
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = MoveInput.X * MovementSpeed * DeltaTime;
	DeltaLocation.Y = MoveInput.Y * MovementSpeed * DeltaTime;
	DeltaLocation.Z = 0.0f;

	AddActorLocalOffset(DeltaLocation, true);
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D LookInput = value.Get<FVector2D>();
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	// 좌우 회전: 캐릭터 몸 전체 회전
	const float DeltaYaw = LookInput.X * RotationSpeed * DeltaTime;
	AddActorLocalRotation(FRotator(0.0f, DeltaYaw, 0.0f));

	// 상하 회전: SpringArm만 회전
	const float DeltaPitch = LookInput.Y * RotationSpeed * DeltaTime * -1;

	FRotator SpringArmRotation = SpringArmComp->GetRelativeRotation();
	SpringArmRotation.Pitch += DeltaPitch;

	SpringArmRotation.Pitch = FMath::Clamp(SpringArmRotation.Pitch, -60.0f, 30.0f);
	SpringArmRotation.Yaw = 0.0f;
	SpringArmRotation.Roll = 0.0f;

	SpringArmComp->SetRelativeRotation(SpringArmRotation);
}
