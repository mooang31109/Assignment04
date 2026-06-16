// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ASSIGNMENT04_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCharacter();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component")
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component")
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	UCameraComponent* CameraComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Movement")
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Movement")
	float RotationSpeed;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	
public:
	virtual void Tick(float DeltaTime) override;

};
