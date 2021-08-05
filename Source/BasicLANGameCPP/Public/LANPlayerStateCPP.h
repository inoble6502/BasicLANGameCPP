// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/PlayerState.h"
#include "LANPlayerStateCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BASICLANGAMECPP_API ALANPlayerStateCPP : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	FName LANPlayerName; //name given to players on LAN game session
	
	UFUNCTION(BlueprintCallable)
	FName LanPlayerName() const;
	
	UFUNCTION(BlueprintCallable)
	void SetLanPlayerName(const FName& LanPlayerName);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ChangeLanPlayerName(const FName& name);

	//required for replicating variables
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
